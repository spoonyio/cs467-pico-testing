/*
    Portions of this code were adapted from the official Raspberry Pi examples repo
    and is licensed as follows:
    Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
    SPDX-License-Identifier: BSD-3-Clause
    Source: https://github.com/raspberrypi/pico-examples/tree/master/i2c/lcd_1602_i2c
*/
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "display.h"

static i2c_inst_t *lcd_i2c;
static uint lcd_sda, lcd_scl;
static uint8_t lcd_addr;

static void lcd_send_nibble(uint8_t nibble, bool rs) {
    uint8_t data = (nibble & 0xF0) | (rs ? 0x01 : 0x00) | 0x08;
    uint8_t seq[2] = { (uint8_t)(data | 0x04), data };
    i2c_write_blocking(lcd_i2c, lcd_addr, seq, 2, false);
}

static void lcd_send_byte(uint8_t val, bool rs) {
    lcd_send_nibble(val & 0xF0, rs);
    lcd_send_nibble((val << 4) & 0xF0, rs);
    sleep_us(50);
}

static void lcd_cmd(uint8_t c)  { lcd_send_byte(c, false); }
static void lcd_data(uint8_t d) { lcd_send_byte(d, true);  }

void display_init(i2c_inst_t *i2c, uint sda, uint scl, uint8_t addr) {
    lcd_i2c = i2c;
    lcd_sda = sda;
    lcd_scl = scl;
    lcd_addr = addr;

    i2c_init(lcd_i2c, 100 * 1000);
    gpio_set_function(lcd_sda, GPIO_FUNC_I2C);
    gpio_set_function(lcd_scl, GPIO_FUNC_I2C);
    gpio_pull_up(lcd_sda);
    gpio_pull_up(lcd_scl);

    sleep_ms(50);
    lcd_cmd(0x33);
    lcd_cmd(0x32);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
    sleep_ms(5);
}

void display_clear(void) {
    lcd_cmd(0x01);
    sleep_ms(2);
}

void display_set_cursor(uint8_t col, uint8_t row) {
    static const uint8_t row_offsets[] = {0x00, 0x40};
    lcd_cmd(0x80 | (col + row_offsets[row & 0x01]));
}

void display_print(const char *text) {
    while (*text) lcd_data((uint8_t)*text++);
}
