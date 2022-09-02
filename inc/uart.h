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
#define CMD_CODE 0x23
#define SEND_CODE 0x16

#define SEND_TIME 0xD6

#define REQUEST_USER_CMD 0xc3

#define SEND_REF_CODE 0xD2
#define SEND_CONTROL_MODE 0xD4
#define READ_USER_CMD 0xC3
#define UART_SLEEP_TIME 100000

int init_uart();
void setup_uart();
int write_uart(int uart, unsigned char *message, int size);
float read_float(int uart);
int read_int(int uart);

#endif