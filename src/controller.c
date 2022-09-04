#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "uart.h"
#include "gpio.h"
#include "pid.h"
#include "controller.h"
#include "lcd_display.h"
#include "../inc/menu.h"
#include "lcd_display.h"
#include "timer.h"
#include "modbus.h"

Controller controller = {0, 0, 0, 0, 0.0};

void set_system_state(int state)
{
    controller.system_state = state;
}

void set_uart_controller(int uart)
{
    controller.uart = uart;
}

void signal_control(int control_output)
{
    unsigned char control_signal[11] = {ESP_CODE, SEND_CODE, SEND_CONTROL_SIGNAL, MATRICULA};

    memcpy(&control_signal[7], &control_output, 4);
    write_uart(controller.uart, control_signal, 11);
}

void run_control()
{
    unsigned char temp_code[7] = {ESP_CODE, SEND_CODE, TEMP_CODE, MATRICULA};
    unsigned char potenciometro_code[7] = {ESP_CODE, SEND_CODE, POTENCIOMETRO_CODE, MATRICULA};
    unsigned char temp_ref[11] = {ESP_CODE, SEND_CODE, SEND_REF_CODE, MATRICULA};

    float potenciometro_value;
    float internal_temp;
    float control_output;
    float tr;
    Timer time;
    if (controller.system_state == 0)
    {
        printf("SISTEMA DESLIGADO\n");
    }
    else if (controller.is_heating)
    {
        write_uart(controller.uart, temp_code, 7);

        read_message(controller.uart, temp_code, &internal_temp, 4);

        // REF MODE CASES
        control_output = pid_controle(internal_temp);
        switch (controller.ref_mode)
        {

        case UART_MODE:
            time = get_time();
            write_uart(controller.uart, potenciometro_code, 7);

            read_message(controller.uart, potenciometro_code, &potenciometro_value, 4);

            pid_atualiza_referencia(potenciometro_value);
            display_air_fryer_info(potenciometro_value, internal_temp, time.sec);

            if (internal_temp >= potenciometro_value)
            {

                set_time_is_decreasing(1);
            }
            if (time.is_decreasing == 1)
            {

                decrease_1sec_timer();
            }

            if (time.sec <= 0 && time.is_decreasing)
            {
                set_time_is_decreasing(0);
                send_system_running_state(0);
            }

            break;
        case TERMINAL_MODE:
            tr = get_pid_ref();
            time = get_time();

            memcpy(&temp_ref[7], &tr, 4);
            write_uart(controller.uart, temp_ref, 11);
            display_air_fryer_info(tr, internal_temp, time.sec);

            break;
        default:
            break;
        }

        if (control_output > 0)
        {
            start_resistor((int)control_output);
            stop_fan();
        }
        else
        {
            if (control_output < -PWM_LIMIT)
            {
                start_fan((int)(-1.0 * control_output));
            }
            else
            {
                start_fan(PWM_LIMIT);
            }
            stop_resistor();
        }
        signal_control(control_output);
    }
}

void set_mode(int ref_mode)
{
    controller.ref_mode = ref_mode;
}

void set_pid_ref(float ref)
{
    controller.pid_ref = ref;
}

float get_pid_ref()
{
    return controller.pid_ref;
}

void send_system_state(int system_state)
{
    controller.system_state = system_state;
    unsigned char send_system_state[11] = {ESP_CODE, SEND_CODE, SEND_SYSTEM_STATE, MATRICULA};
    int system_char = (char)controller.system_state;
    memcpy(&send_system_state[7], &system_char, 1);
    write_uart(controller.uart, send_system_state, 8);
}

void send_system_running_state(int heating_state)
{
    controller.is_heating = heating_state;
    unsigned char send_system_state[11] = {ESP_CODE, SEND_CODE, SEND_RUNNING_STATE, MATRICULA};
    int system_heating_char = (char)controller.is_heating;
    memcpy(&send_system_state[7], &system_heating_char, 1);
    write_uart(controller.uart, send_system_state, 8);

    if (heating_state)
    {
        printf("SYSTEM IS HEATING\n");
    }
    else
    {
        printf("SYSTEM IS STOPPING HEATING\n");
    }
}

void handle_user_command(int command)
{
    switch (command)
    {
    case TURN_ON:
        send_system_state(1);
        set_time(0);
        display_message("Ligado");
        printf("System turned on\n");
        break;
    case TURN_OFF:
        stop_resistor();
        stop_fan();
        send_system_state(0);
        display_message("Desligado!");
        printf("System turned off\n");
        break;
    case INIT_HEATING:
        display_message("Aquecendo...");
        send_system_running_state(1);
        printf("Start heating \n");
        break;
    case CANCEL_HEATING:
        display_message("Parado");
        send_system_running_state(0);
        printf("Stopping heating\n");
        break;
    case INCREASE_TIME:
        increase_timer();
        printf("Increasing time\n");
        break;
    case DECREASE_TIME:
        decrease_1min_timer();
        printf("Decreasing time\n");
        break;
    default:
        break;
    }
}

void read_user_command()
{
    unsigned char user_command[7] = {ESP_CODE, CMD_CODE, READ_USER_CMD, MATRICULA};

    write_uart(controller.uart, user_command, 7);
    int command = 0;
    read_message(controller.uart, user_command, &command, 4);

    if (command > 0 && command < 8)
    {

        printf("Command: %d\n", command);
        handle_user_command(command);
    }
}
