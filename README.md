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
