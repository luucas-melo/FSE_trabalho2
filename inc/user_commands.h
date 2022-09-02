

#define TURN_ON 0x01
#define TURN_OFF 0x02
#define INIT_HEATING 0x03
#define CANCEL_HEATING 0x04
#define INCREASE_TIME 0x05
#define DECREASE_TIME 0x06
#define MENU 0x07

void read_user_command(int uart);
