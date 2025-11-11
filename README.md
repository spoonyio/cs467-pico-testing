# cs467-pico-testing

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
