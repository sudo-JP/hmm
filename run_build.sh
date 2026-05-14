#!/bin/bash
rm -rf build
cmake -B build -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
ninja -C build
rm compile_commands.json
ln -s ./build/compile_commands.json .
./build/TestOpenGL
