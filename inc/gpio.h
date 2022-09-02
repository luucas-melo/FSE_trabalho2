#ifndef GPIO_H_
#define GPIO_H_

#define RESISTOR_PIN 4
#define FAN_PIN 5
#define PWM_MAX 100

int init_gpio();

void start_fan(int pwm);
void stop_fan();

void start_resistor(int pwm);
void stop_resistor();

void gpio_stop_all();

#endif