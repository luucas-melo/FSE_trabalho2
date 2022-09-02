#ifndef UART_H_
#define UART_H_

#define MATRICULA 0x05, 0x08, 0x08, 0x05

#define FILE_DESCRIPTOR "/dev/serial0"
#define UART_FAIL -1

#define TEMP_CODE 0xC1
#define POTENCIOMETRO_CODE 0xC2
#define READ_USER_REF_CODE 0xC3

#define CLIENT_CODE 0x00
#define ESP_CODE 0x01
#define CODIGO_CMD 0x23
#define SEND_CODE 0x16

#define UART_SLEEP_TIME 500000

int init_uart();
void setup_uart();
int write_uart(int uart, unsigned char *message, int size);
float read_float(int uart);

#endif