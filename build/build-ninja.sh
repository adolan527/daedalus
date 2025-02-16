#!/bin/bash

# Run CMake and build
cmake .. -G "Ninja"
cmake --build .

# Keep console open
read -n 1 -s -r -p "Press any key to exit..."
echo