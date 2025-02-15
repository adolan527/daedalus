#!/bin/bash
set -e

# Default to Debug if no argument is provided
BUILD_TYPE=${1:-Debug}


cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE
cmake --build .
