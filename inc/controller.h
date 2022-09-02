typedef struct Controller
{
    int state_on_off;
    int uart;
} Controller;

void run_control();

void set_on_off_state(int state);

void set_uart_controller(int uart);
