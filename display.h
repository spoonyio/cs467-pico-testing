#ifndef DISPLAY_H
#define DISPLAY_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

void display_init(i2c_inst_t *i2c, uint sda, uint scl, uint8_t addr);
void display_clear(void);
void display_set_cursor(uint8_t col, uint8_t row);
void display_print(const char *text);

#endif