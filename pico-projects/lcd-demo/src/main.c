#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "../lcd-lib/lcd-lib.h"

int main()
{
    stdio_init_all(); // setup stdio for logging debug messages
    // Make the SPI pins available to picotool
    bi_decl(bi_3pins_with_func(PICO_DEFAULT_SPI_RX_PIN, PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI));
    // Make the CS pin available to picotool
    bi_decl(bi_1pin_with_name(PICO_DEFAULT_SPI_CSN_PIN, "SPI CS"));

    // setup lcd module and gpio pins on the pi pico
    lcd_init();
    // main loop
    while (1)
    {
        int c=1;
        // todo
        printf("test");
    }

}