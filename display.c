/*
    Portions of this code were adapted from the official Raspberry Pi examples repo
    and is licensed as follows:
    Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
    SPDX-License-Identifier: BSD-3-Clause
    Source: https://github.com/raspberrypi/pico-examples/tree/master/i2c/lcd_1602_i2c
*/

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5
#define LCD_ADDR 0x27

void lcd_send_byte(uint8_t val, bool rs) {
    uint8_t high = val & 0xF0;
    uint8_t low  = (val << 4) & 0xF0;
    uint8_t buf[4];

    for (int i = 0; i < 2; i++) {
        uint8_t data = (i == 0 ? high : low) | (rs ? 0x01 : 0x00) | 0x08;
        buf[0] = data | 0x04;
        buf[1] = data;
        i2c_write_blocking(I2C_PORT, LCD_ADDR, buf, 2, false);
    }
    sleep_us(50);
}

void lcd_command(uint8_t cmd) { lcd_send_byte(cmd, false); }
void lcd_char(char c) { lcd_send_byte(c, true); }

void lcd_init() {
    sleep_ms(50);
    lcd_command(0x33);
    lcd_command(0x32);
    lcd_command(0x28);
    lcd_command(0x0C);
    lcd_command(0x06);
    lcd_command(0x01);
    sleep_ms(5);
}

void lcd_set_cursor(uint8_t col, uint8_t row) {
    static const uint8_t row_offsets[] = {0x00, 0x40};
    lcd_command(0x80 | (col + row_offsets[row]));
}

void lcd_print(const char *s) {
    while (*s) lcd_char(*s++);
}

int main() {
    stdio_init_all();

    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    lcd_init();

    lcd_set_cursor(0, 0);
    lcd_print("Hello World!");

    lcd_set_cursor(0, 1);
    lcd_print("CS 467 Capstone");

    while (true) tight_loop_contents();
}
