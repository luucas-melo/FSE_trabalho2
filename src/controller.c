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

Controller controller = {0, 0, 0, 0, 0.0};

int timer = 0;

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
    int co_int = (int)control_output;
    memcpy(&control_signal[7], &co_int, 4);
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
    double tr;

    if (controller.is_heating)
    {
        write_uart(controller.uart, temp_code, 7);
        usleep(UART_SLEEP_TIME);
        internal_temp = read_float(controller.uart);

        // REF MODE CASES
        control_output = pid_controle(internal_temp);
        switch (controller.ref_mode)
        {

        case UART_MODE:
            write_uart(controller.uart, potenciometro_code, 7);
            usleep(UART_SLEEP_TIME);
            potenciometro_value = read_float(controller.uart);
            display_air_fryer_info(potenciometro_value, internal_temp, 2);
            break;
        case TERMINAL_MODE:
            tr = get_pid_ref();
            printf("TR === %f\n", tr);
            memcpy(&temp_ref[7], &tr, 4);
            write_uart(controller.uart, temp_ref, 11);
            usleep(UART_SLEEP_TIME);
            display_air_fryer_info(tr, internal_temp, 2);
            break;
        }

        printf("POTENC VALUE %f\n", potenciometro_value);

        pid_atualiza_referencia(potenciometro_value);

        if (control_output > 0)
        {
            start_resistor((int)control_output);
            stop_fan();
        }
        else
        {
            if (control_output < -40.0)
            {
                start_fan((int)(-1.0 * control_output));
            }
            else
            {
                start_fan(40.0);
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

void send_system_state()
{
    unsigned char send_system_state[11] = {ESP_CODE, SEND_CODE, SEND_SYSTEM_STATE, MATRICULA};
    int system_char = (char)controller.system_state;
    memcpy(&send_system_state[7], &system_char, 1);
    write_uart(controller.uart, send_system_state, 8);
    usleep(UART_SLEEP_TIME);

    int response_code;
    response_code = read_int(controller.uart);
    printf("System state: %d\n", response_code);
}

void handle_user_command(int command)
{
    switch (command)
    {
    case TURN_ON:
        controller.system_state = 1; // ligado
        send_system_state();
        printf("System turned on\n");
        break;
    case TURN_OFF:
        controller.system_state = 0; // desligado
        stop_resistor();
        stop_fan();
        send_system_state();
        display_message("Desligado!");
        printf("System turned off\n");
        break;
    case INIT_HEATING:
        controller.is_heating = 1;
        display_message("Aquecendo...");
        printf("Start heating \n");
        break;
    case CANCEL_HEATING:
        controller.is_heating = 0;
        display_message("Parado");
        printf("Stopping heating\n");
        break;
    default:
        break;
    }
}

void read_user_command()
{
    unsigned char user_command[7] = {ESP_CODE, CMD_CODE, READ_USER_CMD, MATRICULA};

    write_uart(controller.uart, user_command, 7);
    usleep(UART_SLEEP_TIME);
    int command = 0;
    command = read_int(controller.uart);
    if (command > 0 && command < 7)
    {

        printf("Command: %d\n", command);
        handle_user_command(command);
    }
}
