#include <stdio.h>
#include <stdlib.h>
#include <uart.h>
#include <pid.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <signal.h>
#include <sys/signal.h>
#include <controller.h>
#include <gpio.h>
#include "timer.h"
#include "bme280_driver.h"
#include "i2c_lcd.h"
#include "modbus.h"
#include "menu.h"

int uart0 = -1;

void handle_sigint()
{
    set_system_state(0);
    lcd_init();
    ClrLcd();
    stop_fan();
    stop_resistor();
    gpio_stop_all();
    close_uart(uart0);
    exit(0);
}

int main()
{
    uart0 = init_uart();
    init_gpio();
    lcd_init();
    stop_fan();
    stop_resistor();
    sleep(3);
    init_timer(uart0);
    init_sensor();
    set_system_state(0);
    pid_configura_constantes(30.0, 0.2, 400.0);
    menu();
    signal(SIGINT, handle_sigint);
    while (1)
    {

        run_control();
        read_user_command();
        sleep(1);
    }
    close_uart(uart0);
    return 0;
}