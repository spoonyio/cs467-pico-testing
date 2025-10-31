#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "led_array.h"
#include "display.h"

#define I2C_PORT i2c0
#define I2C_SDA  4
#define I2C_SCL  5
#define LCD_ADDR 0x27

int main() {
    stdio_init_all();

    // LCD
    display_init(i2c0, 4, 5, 0x27);
    display_set_cursor(0, 0);
    display_print("Hello World!");
    display_set_cursor(0, 1);
    display_print("CS 467 Capstone");

    // LEDs
    led_array_init();
    led_array_show_loading(2000);
    while (true) {
        float tests[] = {0, 5, 12.5, 25, 37.5, 50, 62.5, 75, 87.5, 100};
        int n = sizeof(tests) / sizeof(tests[0]);

        for (int pass = 0; pass < 2; ++pass) {
            for (int i = 0; i < n; ++i) {
                float h = tests[i];
                uint8_t leds_on = humidity_to_leds(h);
                led_array_set(leds_on);
                sleep_ms(400);
            }
        }
        for (int i = 2; i <= 8; i *= 2) {
            led_array_show_error(i, 2000);
            led_array_show_loading(2000);
        }
    }

}