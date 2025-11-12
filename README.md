# Microcontroller Home Humidity Sensor (Test)

Current version [11/12/2025]: Updated to Code Review #2 progress. Small modifications made in main.c and sensor.c that are divergent from teammates in order to make everything work together, those changes will be noted in the code reviews in the main repo.

1. Open codespaces, type:
   - `rm -rf build`
   - `cmake -S . -B build -G "Ninja"`
   - `cmake --build build`
2. Download `.uf2` firmware that was created in the build folder
3. Flash pico with that `.uf2`
   - unplug pico
   - hold down BOOTSEL button
   - plug in pico
   - pico should appear as RPI-RP2
   - drag and drop `.uf2` into it

_Note: Ignore the folder `bus_scan_test`. It's an independent test from the pico sdk. If you'd like to compile it to test on your pico just do the instructions above inside of the folder._
