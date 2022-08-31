#include "uart.h"
#include "crc16.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

void setup_uart(int uart0)
{
    printf("Setting up UART...\n");
    struct termios options;
    tcgetattr(uart0, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0, TCIFLUSH);
    tcsetattr(uart0, TCSANOW, &options);
    printf("✓ Uart setted up with success\n");
}

int init_uart()
{
    int uart = -1;
    printf("Setting up uart... ");

    uart = open(FILE_DESCRIPTOR, O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart == UART_FAIL)
    {
        printf("Error on open uart\n");
        exit(1);
    }
    else
    {
        setup_uart(uart);
    }
    return uart;
}

void close_uart(int uart0)
{
    close(uart0);
    printf("✓ Uart close with success.\n");
}

int write_uart(int uart0, unsigned char *message, int size)
{
    unsigned char tx_buffer[200];
    short crc = calcula_CRC(message, size);
    memcpy(tx_buffer, message, size);
    memcpy(&tx_buffer[size], &crc, 2);

    int count = write(uart0, tx_buffer, size + 2);
    if (count < 0)
    {
        printf("Error: Write uart error\n");
        return UART_FAIL;
    }
    else
    {
        printf("✓ Writed with success.\n");
    }

    return 0;
}
