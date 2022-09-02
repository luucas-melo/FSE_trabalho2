#include <uart.h>

typedef struct Timer
{

    int uart;
    int time;

} Timer;

Timer timer;
void initTimer(int uart)
{
    timer.time = 0;
    timer.uart = uart;
}

void increase_timer()
{
    printf("TIMER: %d\n", timer);
    timer.time++;
    if (timer.time == 60)
    {
        timer.time = 0;
    }

    // write_uart(timer.uart, timer.time, SEND_TIME);
}