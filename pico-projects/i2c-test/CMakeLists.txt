# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(i2c-test C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(i2c-test i2c-test.c )

pico_set_program_name(i2c-test "i2c-test")
pico_set_program_version(i2c-test "0.1")

pico_enable_stdio_uart(i2c-test 1)
pico_enable_stdio_usb(i2c-test 0)

# Add the standard library to the build
target_link_libraries(i2c-test pico_stdlib)

# Add any user requested libraries
target_link_libraries(i2c-test
        hardware_i2c
        )

pico_add_extra_outputs(i2c-test)

