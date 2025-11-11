cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(humidity_sensor_version_0 C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(humidity_sensor_version_0
    main.c
    display.c
    sensor.c
    led_array.c
)

if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)
    pico_generate_pio_header(humidity_sensor_version_0 ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)
endif()

target_include_directories(humidity_sensor_version_0 PRIVATE .)

target_link_libraries(humidity_sensor_version_0
    pico_stdlib
    hardware_i2c
    hardware_pio
)

pico_enable_stdio_usb(humidity_sensor_version_0 1)
pico_enable_stdio_uart(humidity_sensor_version_0 0)

pico_add_extra_outputs(humidity_sensor_version_0)