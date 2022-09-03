#ifndef UART_H_
#define UART_H_

#define MATRICULA 0x05, 0x08, 0x08, 0x05

#define FILE_DESCRIPTOR "/dev/serial0"
#define UART_FAIL -1

#define TEMP_CODE 0xC1
#define POTENCIOMETRO_CODE 0xC2
#define READ_USER_CMD 0xC3

#define RETURN_CODE 0x00
#define ESP_CODE 0x01
#define CMD_CODE 0x23
#define SEND_CODE 0x16

// SEND DATA
#define SEND_CONTROL_SIGNAL 0xD1
#define SEND_REF_CODE 0xD2
#define SEND_SYSTEM_STATE 0xD3
#define SEND_CONTROL_MODE 0xD4
#define SEND_RUNNING_STATE 0xD5
#define SEND_TIME 0xD6

// UART MENU RESPONSES
#define TURN_ON 0x01
#define TURN_OFF 0x02
#define INIT_HEATING 0x03
#define CANCEL_HEATING 0x04
#define INCREASE_TIME 0x05
#define DECREASE_TIME 0x06
#define MENU 0x07

int init_uart();
void setup_uart();
int write_uart(int uart, unsigned char *message, int size);

#endif