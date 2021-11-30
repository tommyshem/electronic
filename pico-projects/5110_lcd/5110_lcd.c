#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pcd8544_lcd.h"

int main()
{
    stdio_init_all(); // setup stdio for logging debug messages
 // Make the SPI pins available to picotool
    bi_decl(bi_3pins_with_func(PICO_DEFAULT_SPI_RX_PIN, PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI));
     // Make the CS pin available to picotool
    bi_decl(bi_1pin_with_name(PICO_DEFAULT_SPI_CSN_PIN, "SPI CS"));
    
    // main loop
    do
    {
        // todo
    } while (1);
}
