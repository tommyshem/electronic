#include "lcd-lib.h"

/*
 *******************************************************************
               Public LCD functions below
 *******************************************************************
*/

/*! Setup the rp2040 pins direction and setup the lcd module
 \param SCLK  Pin number for the Serial Clock on the LCD display
 \param DIN	Pin number for the data in on the LCD display
 \param DC	Pin number
 \param RST	Pin number Reset the data in on the LCD display
*/
void lcd_init()
{

// *******************************************************
// setup gpio pins on the pi pico
// *******************************************************

    // SPI initialisation. SPI at 1MHz.
    spi_init(SPI_PORT, 1000 * 1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

// chip select pin setup
#if PIN_CS > 0
    gpio_set_function(PIN_CS, GPIO_FUNC_SIO);
    gpio_set_dir(PIN_CS, GPIO_OUT);
#endif
// reset pin setup
#if PIN_RST > 0
    gpio_set_function(PIN_RST, GPIO_FUNC_SIO);
    gpio_set_dir(PIN_RST, GPIO_OUT);
#endif
    // data command pin setup
    gpio_set_function(PIN_DC, GPIO_FUNC_SIO);
    gpio_set_dir(PIN_DC, GPIO_OUT);

// ****************************************************
// setup the lcd module
// ****************************************************

// toggle lcd RST low to reset (is active-low, so we'll initialise it to a driven-high state)
#if PIN_RST > 0
    gpio_put(PIN_RST, LOW);
    sleep_ms(500);
    gpio_put(PIN_RST, HIGH);
#endif
   
lcd_write_command(FUNCTION_SET_COMMAND+FUNCTION_SET_NORMAL);
lcd_write_command(DISPLAY_CONTROL_COMMAND+DISPLAY_ALL_ON);
lcd_write_command_data(255);


}



void lcd_clear_screen()
{
}

void lcd_set_cursor(uint8_t x, uint8_t y)
{
}

// draw directly to the lcd screen using column (x) row (y) coordinates and pixel_colour BLACK or WHITE
void lcd_draw_pixel(uint8_t column, uint8_t row, uint8_t pixel_color)
{
    // check max coordinates and exit if to big
    if ((column < 0) || (column > LCDWIDTH) || (row < 0) || (row >= LCDHEIGHT))
        return;

    // x is column or y is the row
    if (pixel_color)
    fix(); // todo update buffer with pixel
    else
    fix();  // todo update buffer with clear pixel
    // todo display updated buffer
}

void fix(){
    printf("needs fixing");
}

//****************************************************************
//               Internal functions used below
//****************************************************************

/*
send command ram data to the lcd module

Write data - bits order
D/C  B7 B6 B5 B4 B3 B2 B1 B0
1    D7 D6 D5 D4 D3 D2 D1 D0
*/
void lcd_write_command_data(uint8_t d)
{
    gpio_put(PIN_DC, HIGH);
    cs_select();
    spi_write_blocking(SPI_PORT, &d, 1);
    cs_deselect();
}

/*
send command to the lcd module

Lcd Commands
Function set
D/C  B7 B6 B5 B4 B3 B2 B1 B0
0    0  0  1  0  0  PD V  H
PD  - Chip is active Chip is in Power-down mode
V   - Horizontal addressing Vertical addressing
H   - Use basic instruction set   Use extended instruction set


Display control
D/C  B7 B6 B5 B4 B3 B2 B1 B0
0    0  0  0  0  1  D  0  E
D and E
    00 Display blank
    10 Normal mode
    01 All display segments on
    11 Inverse video mode
*/
void lcd_write_command(uint8_t c)
{
    gpio_put(PIN_DC, LOW);
    cs_select();
    spi_write_blocking(SPI_PORT, &c, 1);
    cs_deselect();
}