//
// Created by tommy on 01/12/2021.
//

#ifndef UNTITLED_LCD_LIB_H
#define UNTITLED_LCD_LIB_H
#endif //UNTITLED_LCD_LIB_H

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

Lcd module pin layout with default pi pico gpio used

pin label                       pin function
1   VSS 2.7v - 3.3V     36      positive supply
2   0v                  23      negative supply
3   SCE                GP18     chip select  active low
4   RST                GP20     reset active low
5   D/C                GP21     mode select LOW command mode HIGH write data mode
6   DN(MOSI)           GP19     serial data in
7   SCLK               GP17     serial clock
8   led                         led backlight supply max voltage 3.3v - 330 ohm to pwm pin



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

0

*********************************************************************/
// pins on rp2040 (Pico) to be used
#define SPI_PORT spi0 // spi to use on rp2040
#define PIN_MISO PICO_DEFAULT_SPI_RX_PIN  // gpio 16 spi out
#define PIN_CS PICO_DEFAULT_SPI_CSN_PIN    // gpio 17 chip select pin - set to 0 if wiring to 0v
#define PIN_SCK  PICO_DEFAULT_SPI_SCK_PIN   // gpio 18 spi clock
#define PIN_MOSI PICO_DEFAULT_SPI_TX_PIN  //gpio 19   spi in
#define PIN_RST 20    // reset pin - set to 0 if wiring to 0v
#define PIN_DC 21     // data command pin
//LCD colors
#define BLACK 1
#define WHITE 0
//setup LCD screen size
#define LCDWIDTH 84
#define LCDHEIGHT 48

// function set commands
#define FUNCTION_SET_COMMAND 32
// only use one of the flags at a time with the command function set above
// e.g FUNCTION_SET_COOMAND+FUNCTION_SET_NORMAL
#define FUNCTION_SET_NORMAL 0
#define FUNCTION_SET_POWERDOWN 4
#define FUNCTION_SET_VERTICAL_MODE 2 // horz addressing vertical addressing
#define FUNCTION_SET_EXTENDED_INSTRUCTION 1

// display control commands
#define DISPLAY_CONTROL_COMMAND 8
// only use one of the flags at a time with the command display control above
// e.g DISPLAY_CONTROL_COMMAND+DISPLAY_BLANK
#define DISPLAY_BLANK 0
#define DISPLAY_NORMAL 4
#define DISPLAY_ALL_ON 1
#define DISPLAY_INVERTED 5

// set y address
#define COMMAND_SET_Y_ADDRESS 64
// set x address
#define COMMAND_SET_X_ADDRESS 128
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
// lcd module api

void lcd_init();

void lcd_clear_screen();

void lcd_set_cursor(uint8_t x,uint8_t y);

void lcd_draw_pixel(uint8_t x, uint8_t y, uint8_t c);
