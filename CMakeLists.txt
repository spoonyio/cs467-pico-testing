cmake_minimum_required(VERSION 3.13)

if(NOT DEFINED ENV{PICO_SDK_PATH})
    message(FATAL_ERROR "PICO_SDK_PATH not set")
endif()
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_testing C CXX ASM)

# Initialize the SDK (must come after import and before any pico_* commands)
pico_sdk_init()

add_executable(pico-testing
    blink.c
)

target_link_libraries(pico-testing pico_stdlib)

pico_add_extra_outputs(pico-testing)

add_executable(ws2812
    ws2812.c
)

pico_generate_pio_header(ws2812 ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

target_link_libraries(ws2812
    pico_stdlib
    hardware_pio
    hardware_clocks
)

pico_add_extra_outputs(ws2812)
