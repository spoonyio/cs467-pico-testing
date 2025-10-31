cmake_minimum_required(VERSION 3.13)

if(NOT DEFINED ENV{PICO_SDK_PATH})
    message(FATAL_ERROR "PICO_SDK_PATH not set")
endif()
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico-testing C CXX ASM)
pico_sdk_init()

add_executable(pico-testing
    main.c
    led_array.c
    display.c
)

target_link_libraries(pico-testing
    pico_stdlib
    hardware_pio
    hardware_clocks
    hardware_i2c
)

pico_generate_pio_header(pico-testing ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

pico_add_extra_outputs(pico-testing)