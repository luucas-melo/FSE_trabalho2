#include "gpio.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <softPwm.h>

int init_gpio()
{
    if (wiringPiSetup() == -1)
    {
        printf("Error: Fail to start wiringPi\n");
        exit(1);
    }

    pinMode(RESISTOR_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);

    if (softPwmCreate(RESISTOR_PIN, 0, PWM_MAX))
    {
        printf("Error: Failed to configure resistor  %d\n", RESISTOR_PIN);
    }
    if (softPwmCreate(FAN_PIN, 0, PWM_MAX))
    {
        printf("Error: Failed to configure fan: %d\n", FAN_PIN);
    }

    return 0;
}

void start_fan(int pwm)
{
    softPwmWrite(FAN_PIN, pwm);
}

void stop_fan()
{

    softPwmWrite(FAN_PIN, 0);
}

void start_resistor(int pwm)
{
    softPwmWrite(RESISTOR_PIN, pwm);
}

void stop_resistor()
{
    softPwmWrite(RESISTOR_PIN, 0);
}

void gpio_stop_all()
{
    softPwmStop(RESISTOR_PIN);
    softPwmStop(FAN_PIN);
    sleep(1);
}
