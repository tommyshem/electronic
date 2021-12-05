# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)
#Project Name and types which can be used
project(5110_lcd C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(5110_lcd 
                5110_lcd.c
                lcd_lib/pcd8544_lcd.h
                )

# set name and version so pictool can read them
pico_set_program_name(5110_lcd "5110_lcd")
pico_set_program_version(5110_lcd "0.1")

# set which stdio we are using - 1 using 0 not using. Only one can be picked
pico_enable_stdio_uart(5110_lcd 1)
pico_enable_stdio_usb(5110_lcd 0)

# Add the standard library to the build
target_link_libraries(5110_lcd pico_stdlib)

# Add any user requested libraries
target_link_libraries(5110_lcd
        hardware_spi
        )


pico_add_extra_outputs(5110_lcd)

