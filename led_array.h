#ifndef LED_ARRAY_H
#define LED_ARRAY_H

#include <stdint.h>
#include <stdbool.h>

bool led_array_init(void);
uint8_t humidity_to_leds(float h);
void led_array_set(uint8_t leds_on);
void led_array_show_loading(uint32_t ms_total);
void led_array_show_error(uint8_t code, uint32_t ms_total);

#endif