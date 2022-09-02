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
Controller controller;

int timer = 0;

void set_on_off_state(int state)
{
    controller.state_on_off = state;
}

void set_uart_controller(int uart)
{
    controller.uart = uart;
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

    while (1)
    {
        write_uart(controller.uart, temp_code, 7);
        usleep(UART_SLEEP_TIME);
        internal_temp = read_float(controller.uart);
        printf("REF MODE === %d\n", controller.ref_mode);
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
        read_user_command();
        sleep(1);
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
