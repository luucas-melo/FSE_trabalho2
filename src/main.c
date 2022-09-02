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
int uart0 = -1;

int main()
{
    printf("rodou\n");
    uart0 = init_uart();
    init_gpio();
    lcd_init();
    stop_fan();
    stop_resistor();
    sleep(8);
    pid_configura_constantes(30.0, 0.2, 400.0);
    menu();
    run_control();
    close(uart0);
    return 0;
}