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
    float potenciometro_value;
    float internal_temp;
    float control_output;

    while (1)
    {
        write_uart(controller.uart, temp_code, 7);
        usleep(UART_SLEEP_TIME);
        internal_temp = read_float(controller.uart);

        write_uart(controller.uart, potenciometro_code, 7);
        usleep(UART_SLEEP_TIME);
        potenciometro_value = read_float(controller.uart);

        printf("POTENC VALUE %f\n", potenciometro_value);

        pid_atualiza_referencia(potenciometro_value);

        control_output = pid_controle(internal_temp);

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
        display_air_fryer_info(potenciometro_value, internal_temp, 2);

        sleep(1);
    }
}
