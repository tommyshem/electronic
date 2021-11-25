#include <stdio.h>  // for printf
#include "pico/stdlib.h"

#define GPIO_ON 1
#define GPIO_OFF 0

int main() {

    stdio_init_all();  // setup stdio so printf can be used
    printf("\nI2C-Test program\n");

#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, GPIO_ON);
        printf("Led turned on \n");
        sleep_ms(250);
        gpio_put(LED_PIN, GPIO_OFF);
        printf("Led turned off \n");
        sleep_ms(250);
    }
#endif


}