typedef struct Controller
{
    int state_on_off;
    int uart;
    int ref_mode;
    float pid_ref;
} Controller;

void run_control();

void set_on_off_state(int state);

void set_uart_controller(int uart);

void set_mode(int mode);

void set_pid_ref(float ref);

float get_pid_ref();
