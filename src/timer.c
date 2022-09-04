#include <uart.h>
#include <string.h>
#include "timer.h"
#include "stdio.h"

Timer timer = {0, 0, 0, 0};

void init_timer(int uart)
{
    timer.min = 0;
    timer.sec = 0;
    timer.uart = uart;
}

void increase_timer()
{
    unsigned char timer_value[11] = {ESP_CODE, SEND_CODE, SEND_TIME, MATRICULA};

    timer.sec += 60;
    int sec = timer.sec;
    if (sec >= 60)
    {
        timer.min += 1;
        sec = 0;
    }
    memcpy(&timer_value[7], &timer.min, 4);
    write_uart(timer.uart, timer_value, 11);
}

void decrease_1min_timer()
{
    unsigned char timer_value[11] = {ESP_CODE, SEND_CODE, SEND_TIME, MATRICULA};
    timer.sec -= 60;
    timer.min = timer.sec / 60;
    int sec = timer.sec;
    if (sec < 0)
    {
        timer.min = 0;
        timer.sec = 0;
    }
    memcpy(&timer_value[7], &timer.min, 4);
    write_uart(timer.uart, timer_value, 11);
}

void decrease_1sec_timer()
{
    unsigned char timer_value[11] = {ESP_CODE, SEND_CODE, SEND_TIME, MATRICULA};
    timer.sec--;
    timer.min = timer.sec / 60;
    if (timer.sec < 0)
    {
        timer.sec = 0;
    }
    memcpy(&timer_value[7], &timer.min, 4);
    write_uart(timer.uart, timer_value, 11);
}

void set_time(int newTime)
{
    timer.min = newTime;

    unsigned char timer_value[11] = {ESP_CODE, SEND_CODE, SEND_TIME, MATRICULA};

    memcpy(&timer_value[7], &timer.min, 4);
    write_uart(timer.uart, timer_value, 11);
}

void set_time_is_decreasing(int is_decreasing)
{
    timer.is_decreasing = is_decreasing;
}

Timer get_time()
{
    return timer;
}