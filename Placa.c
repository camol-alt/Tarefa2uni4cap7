#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define RED_PIN 13
#define GREEN_PIN 11
#define BLUE_PIN 12
#define PWM_FREQUENCY 5000

void setupPWM(uint pin, uint frequency) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_wrap(slice_num, 255);
    pwm_set_clkdiv(slice_num, (float)48000000 / frequency / 256);
    pwm_set_enabled(slice_num, true);
}

void setLEDBrightness(uint pin, uint8_t brightness) {
    pwm_set_gpio_level(pin, brightness);
}

int main() {
    stdio_init_all();

    setupPWM(RED_PIN, PWM_FREQUENCY);
    setupPWM(GREEN_PIN, PWM_FREQUENCY);
    setupPWM(BLUE_PIN, PWM_FREQUENCY);

    // Configurações iniciais do LED RGB
    setLEDBrightness(RED_PIN, 255);  // Vermelho
    setLEDBrightness(GREEN_PIN, 0);  // Verde
    setLEDBrightness(BLUE_PIN, 0);  // Azul
    sleep_ms(5000);

    setLEDBrightness(RED_PIN, 0);    // Apaga Vermelho
    setLEDBrightness(GREEN_PIN, 255);  // Verde
    setLEDBrightness(BLUE_PIN, 0);    // Azul
    sleep_ms(5000);

    setLEDBrightness(RED_PIN, 0);    // Apaga Vermelho
    setLEDBrightness(GREEN_PIN, 0);  // Apaga Verde
    setLEDBrightness(BLUE_PIN, 255);  // Azul
    sleep_ms(5000);

    while (1) {
        for (uint8_t brightness = 0; brightness <= 255; brightness++) {
            setLEDBrightness(RED_PIN, brightness);
            setLEDBrightness(GREEN_PIN, 255 - brightness);
            setLEDBrightness(BLUE_PIN, brightness / 2);
            sleep_ms(10);
        }

        for (uint8_t brightness = 255; brightness >= 0; brightness--) {
            setLEDBrightness(RED_PIN, brightness);
            setLEDBrightness(GREEN_PIN, 255 - brightness);
            setLEDBrightness(BLUE_PIN, brightness / 2);
            sleep_ms(10);
        }
    }

    return 0;
}
