#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PWM_SERVO 22
const float PWM_FREQ = 50.0;
const float PWM_DIVISER = 64.0;
const uint16_t WRAP = 24000;

void pwm_setup()
{
    gpio_set_function(PWM_SERVO, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(PWM_SERVO);
    pwm_set_clkdiv(slice_num, PWM_DIVISER);
    pwm_set_wrap(slice_num, WRAP);
    pwm_set_enabled(slice_num, true);
}

void set_pwm(uint16_t duty_cycle)
{
    uint slice_num = pwm_gpio_to_slice_num(PWM_SERVO);
    pwm_set_gpio_level(PWM_SERVO, duty_cycle);
}

void move_servo(uint16_t duty_cycle, uint16_t wait_time)
{
    set_pwm(duty_cycle);
    sleep_ms(wait_time);
}

// Função para converter ângulo em ciclo de trabalho PWM
uint16_t angle_to_duty_cycle(float angle)
{
    const uint16_t min_duty_cycle = 500;  // Ciclo mínimo de 0 graus
    const uint16_t max_duty_cycle = 2400; // Ciclo máximo de 180 graus
    return min_duty_cycle + (angle / 180.0) * (max_duty_cycle - min_duty_cycle);
}

void sweep_servo()
{
    for (uint16_t duty_cycle = 500; duty_cycle <= 2400; duty_cycle += 5)
    {
        move_servo(duty_cycle, 10);
    }

    for (uint16_t duty_cycle = 2400; duty_cycle >= 500; duty_cycle -= 5)
    {
        move_servo(duty_cycle, 10);
    }
}

int main()
{
    pwm_setup();

    move_servo(angle_to_duty_cycle(0), 5000); // Servo a 0 graus, aguarda 5 segundos
    move_servo(angle_to_duty_cycle(90), 5000); // Servo a 90 graus, aguarda 5 segundos
    move_servo(angle_to_duty_cycle(180), 5000); // Servo a 180 graus, aguarda 5 segundos

    while (true)
    {
        sweep_servo();
        sweep_servo();
        sweep_servo();
        sweep_servo();
        sweep_servo();
        sweep_servo();
    }

    return 0;
}