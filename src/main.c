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

int uart0 = -1;

int main()
{
    printf("rodou\n");
    uart0 = init_uart();
    unsigned char temp_code[9] = {ESP_CODE, SEND_CODE, TEMP_CODE, MATRICULA};
    write_uart(uart0, temp_code, 7);
    pid_configura_constantes(30.0, 0.2, 400.0);
    return 0;
}