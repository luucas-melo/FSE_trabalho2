#include <uart.h>
#include <string.h>
#include "timer.h"
#include "stdio.h"

Timer timer;

void init_timer(int uart)
{
    timer.time = 0;
    timer.uart = uart;
}

void increase_timer()
{
    unsigned char timer_value[11] = {ESP_CODE, SEND_CODE, SEND_TIME, MATRICULA};

    printf("TIMER INCREASE: %d\n", timer.time);
    timer.time++;
    if (timer.time == 60)
    {
        timer.time = 0;
    }
    memcpy(&timer_value[7], &timer.time, 4);
    write_uart(timer.uart, timer_value, 11);
}

void decrease_timer()
{
    unsigned char timer_value[11] = {ESP_CODE, SEND_CODE, SEND_TIME, MATRICULA};

    printf("TIMER DECREASE: %d\n", timer.time);
    timer.time--;
    if (timer.time < 0)
    {
        timer.time = 0;
    }
    memcpy(&timer_value[7], &timer.time, 4);
    write_uart(timer.uart, timer_value, 11);
}

void set_time(int newTime)
{
    timer.time = newTime;

    unsigned char timer_value[11] = {ESP_CODE, SEND_CODE, SEND_TIME, MATRICULA};

    printf("TIMER: %d\n", timer.time);
    memcpy(&timer_value[7], &newTime, 4);
    write_uart(timer.uart, timer_value, 11);
}

int get_time()
{
    return timer.time;
}