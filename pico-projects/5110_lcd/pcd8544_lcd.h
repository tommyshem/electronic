#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"

/*********************************************************************
This is a library for Monochrome Nokia 5110 LCD Displays

These displays use SPI to communicate, 4 or 5 pins are required to  
interface to the lcd module

max spi speed 4.00MHz

Hookup Guide
https://learn.sparkfun.com/tutorials/graphic-lcd-hookup-guide

pin label               pin function
1   VSS 2.7v - 3.3V     positive supply
2   0v                  negative supply
3   SCE                 chip select  active low
4   RST                 reset   active low
5   D/C                 mode select LOW command mode HIGH write data mode
6   DN(MOSI)            serial data in
7   SCLK                serial clock
8   led                 led backlight supply max voltage 3.3v - 330 ohm to pwm pin

Lcd Commands
Function set
D/C  B7 B6 B5 B4 B3 B2 B1 B0
0    0  0  1  0  0  PD V  H
PD Chip is active Chip is in Power-down mode 
V Horizontal addressing Vertical addressing   
H Use basic instruction set   Use extended instruction set


Display control 
D/C  B7 B6 B5 B4 B3 B2 B1 B0 
0    0  0  0  0  1  D  0  E
D and E 
    00  
    10  
    01  
    11  
 
Display blank 
Normal mode   
All display segments on   
Inverse video mode

Set Y address of RAM
D/C  B7 B6 B5 B4 B3 B2 B1 B0 
0    0  1  0  0  0  Y2 Y1 Y0

Set X address of RAM
D/C  B7 B6 B5 B4 B3 B2 B1 B0 
0    1  X6 X5 X4 X3 X2 X1 X0 

Temperature control 
D/C  B7 B6 B5 B4 B3 B2 B1 B0 
0    0  0  0  0  0  1  T1 T0
T1 and T0 
    00  VLCD temperature coefficient 0 
    01  VLCD temperature coefficient 1
    10  VLCD temperature coefficient 2 
    11  VLCD temperature coefficient 3
 
Bias system

Set VOP

Write data
D/C  B7 B6 B5 B4 B3 B2 B1 B0 
1    D7 D6 D5 D4 D3 D2 D1 D0

*********************************************************************/
// pins on rp2040 (Pico) to be used
#define SPI_PORT spi0 // spi to use on rp2040
#define PIN_MISO 16   // spi out
#define PIN_CS 17     // chip select pin - set to 0 if wiring to 0v
#define PIN_SCK 18    // spi clock
#define PIN_MOSI 19   // spi in
#define PIN_RST 20    // reset pin - set to 0 if wiring to 0v
#define PIN_DC 21     // data command pin
//LCD colors
#define BLACK 1
#define WHITE 0
//setup LCD screen size
#define LCDWIDTH 84
#define LCDHEIGHT 48
// function set commands
#define FUNCTIONSET 32
#define FUNCTION_SET_POWERDOWN 4
#define FUNCTION_SET_VERTICAL_MODE 2 // horz addressing vertical addressing
#define FUNCTION_SET_EXTENDED_INSTRUCTION 1
// display control only one of the flags can be used at a time
#define DISPLAY_CONTROL 8
#define DISPLAY_BLANK 0
#define DISPLAY_NORMAL 4
#define DISPLAY_ALL_ON 1
#define DISPLAY_INVERTED 5
// set y address
#define SET_Y_ADDRESS 64
// set x address
#define SET_X_ADDRESS 128
// temperature control only use one of the flags at a time
#define SET_TEMP 4
#define TEMP_VLCD_0 0
#define TEMP_VLCD_1 1
#define TEMP_VLCD_2 2
#define TEMP_VLCD_3 3
// bias system
#define SET_BIAS 16
// set vop
#define SET_VOP 128
// state
#define LOW 0
#define HIGH 1

// if PIN_CS is set to 0 then do not include this code and the lcd module needs CS pin wiring to 0v
#if PIN_CS > 0
static inline void cs_select()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(PIN_CS, LOW); // Active low
    asm volatile("nop \n nop \n nop");
}

static inline void cs_deselect()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(PIN_CS, HIGH);
    asm volatile("nop \n nop \n nop");
}
#endif

// Setup The pins for the LCD display
// param SCLK  Pin number for the Serial Clock on the LCD display
// param DIN	Pin number for the data in on the LCD display
// param DC	Pin number
// param RST	Pin number Reset the data in on the LCD display

void lcd_init()
{

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

// toggle lcd RST low to reset (is active-low, so we'll initialise it to a driven-high state)
#if PIN_RST > 0
    gpio_put(PIN_RST, LOW);
    sleep_ms(500);
    gpio_put(PIN_RST, HIGH);
#endif
    // setup the lcd module
}

// send command to the lcd module
static void lcd_command(uint8_t c)
{
    gpio_put(PIN_DC, LOW);
    cs_select();
    spi_write_blocking(SPI_PORT, &c, 1);
    cs_deselect();
}

// send command ram data to the lcd module
static void lcd_command_data(uint8_t d)
{
    gpio_put(PIN_DC, HIGH);
    cs_select();
    spi_write_blocking(SPI_PORT, &d, 1);
    cs_deselect();
}
