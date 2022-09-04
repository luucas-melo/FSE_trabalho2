#include <uart.h>

typedef struct Timer
{

    int uart;
    int min;
    int sec;
    int is_decreasing;

} Timer;

void init_timer(int uart);

void increase_timer();
void decrease_1min_timer();
void decrease_1sec_timer();

void set_time(int newTime);
Timer get_time();
void set_time_is_decreasing(int is_decreasing);
