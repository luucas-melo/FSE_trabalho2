#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "uart.h"
#include "user_commands.h"

void read_user_command(int uart)
{
    printf("TRYING TO READ");
    unsigned char command[7] = {ESP_CODE, CMD_CODE, READ_USER_CMD, MATRICULA};

    write_uart(uart, command, 7);
    usleep(UART_SLEEP_TIME);
    int response_code;
    response_code = read_int(uart);
    if (response_code)
    {
        printf("Command: %d\n", response_code);
    }
}
