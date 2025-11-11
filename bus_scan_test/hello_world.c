#include "pico/stdlib.h"
#include <stdio.h>

int main() {
    stdio_init_all();
    sleep_ms(1000);

    while (true) {
        printf("Hello World from Pico over USB!\n");
        sleep_ms(1000);
    }
}