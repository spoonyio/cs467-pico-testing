/*
File: main_basic_test.c (TEMPORARY)
Description:
    This version of main.c simply tests the functionality of the sensor module
    getting readings and sending them to the lcd display and led strip
    for visualization.
*/

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "display.h"
#include "sensor.h"
#include "led_array.h"

#ifndef LCD_I2C_ADDR
#define LCD_I2C_ADDR 0x27
#endif

static inline float clamp01(float x) {
    if (x < 0.f)   return 0.f;
    if (x > 100.f) return 100.f;
    return x;
}

int main(void) {
    stdio_init_all();
    sleep_ms(200);

    i2c_init(I2C_PORT, I2C_FREQ);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    display_init(I2C_PORT, I2C_SDA_PIN, I2C_SCL_PIN, LCD_I2C_ADDR);
    dht_init();

    led_array_init();
    led_array_show_loading(1500);

    display_clear();
    display_set_cursor(0, 0);
    display_print("Humidity");

    char line[21];
    dht_reading r;

    while (true) {
        read_from_dht(&r);

        float rh = clamp01(r.humidity);

        // Update LEDs based on humidity
        humidity_to_leds(rh);

        // Update LCD based on humidity
        display_clear();
        display_set_cursor(0, 0);
        snprintf(line, sizeof(line), "Humidity: %.2f%%", rh);
        display_print(line);

        // Temperature could be second line of LCD

        sleep_ms(500);
    }
}