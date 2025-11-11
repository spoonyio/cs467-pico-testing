cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(i2c_bus_scan C CXX ASM)

pico_sdk_init()

# Your target
add_executable(i2c_bus_scan
    bus_scan.c
)

target_link_libraries(i2c_bus_scan
    pico_stdlib
    hardware_i2c
)

add_executable(hello_world hello_world.c)
target_link_libraries(hello_world pico_stdlib)
pico_add_extra_outputs(hello_world)

pico_enable_stdio_usb(hello_world 1)
pico_enable_stdio_uart(hello_world 0)
add_compile_definitions(PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS=5000)


# printf over USB, not UART
pico_enable_stdio_usb(i2c_bus_scan 1)
pico_enable_stdio_uart(i2c_bus_scan 0)

pico_add_extra_outputs(i2c_bus_scan)