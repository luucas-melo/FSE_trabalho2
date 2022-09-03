#include <uart.h>

typedef struct Timer
{

    int uart;
    int time;

} Timer;

void init_timer(int uart);

void increase_timer();
void decrease_timer();

void set_time(int newTime);
int get_time();
