#define PWM_LIMIT 40.0

typedef struct Controller
{
    int system_state;
    int uart;
    int ref_mode;
    float pid_ref;
    int is_heating;
} Controller;

void run_control();

void set_system_state(int state);

void set_uart_controller(int uart);

void set_mode(int mode);

void set_pid_ref(float ref);

float get_pid_ref();

void read_user_command();
void handle_user_command(int command);
void signal_control(int control_output);

void send_system_state(int system_state);

void send_system_running_state(int heating_state);