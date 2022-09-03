#include <string.h>
#include "modbus.h"
#include "uart.h"

int read_modbus(int uart, void *buffer, int size)
{
    int rx_length = -1;
    int receive_count = 0;
    int timeout = 12;
    while (receive_count < size && timeout)
    {
        rx_length = read(uart, buffer, 1);
        if (rx_length > 0)
        {
            receive_count++;
            buffer++;
        }
        else
        {
            usleep(SLEEP_TIME);
            timeout--;
        }
    }
    return size;
}

int read_message(int uart, unsigned char *code, void *data, int size)
{
    unsigned char rx_buffer[255];
    short expected_crc;
    short computed_crc;
    int buffer_cont = 0;

    while (1)
    {
        switch (buffer_cont)
        {
        case 0:
            if (read_modbus(uart, &rx_buffer[buffer_cont], 1) && (rx_buffer[buffer_cont] == RETURN_CODE))
            {

                buffer_cont++;
            }
            break;
        case 1:
            if (read_modbus(uart, &rx_buffer[buffer_cont], 1) && (rx_buffer[buffer_cont] == code[1]))
            {

                buffer_cont++;
            }
            else
            {
                buffer_cont = 0;
            }
            break;
        case 2:
            if (read_modbus(uart, &rx_buffer[buffer_cont], 1) && (rx_buffer[buffer_cont] == code[2]))
            {

                buffer_cont++;
            }
            else
            {
                buffer_cont = 0;
            }
            break;
        case 3:
            if (read_modbus(uart, &rx_buffer[buffer_cont], size))
            {
                memcpy(data, &rx_buffer[buffer_cont], size);
                buffer_cont++;
            }
            else
            {
                buffer_cont = 0;
            }
            break;
        case 4:
            if (read_modbus(uart, &expected_crc, 2))
            {
                computed_crc = calcula_CRC(rx_buffer, size + 3);
                return (computed_crc == expected_crc) ? 0 : -1;
            }
            else
            {
                return -1;
            }
            break;
        default:

            return -1;
            break;
        }
    }
    return 0;
}