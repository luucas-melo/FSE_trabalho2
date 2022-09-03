#define SLEEP_TIME 100000

int read_modbus(int uart, void *buffer, int size);
int read_message(int uart, unsigned char *code, void *message, int size);