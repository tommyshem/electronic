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

add_executable(${PROJECT_NAME} src/main.c lcd-lib/lcd-lib.c lcd-lib/lcd-lib.h)

# set name and version so pictool can read them
pico_set_program_name(${PROJECT_NAME} "5110_lcd")
pico_set_program_version(${PROJECT_NAME} "0.1")

# set which stdio we are using for printf - 1 using 0 not using. Only one can be picked
pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_enable_stdio_usb(${PROJECT_NAME} 0)

# Add the standard library to the build
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_spi )

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})
