#!/bin/bash


# Check for argument
if [ -z "$1" ]; then
    echo "Usage: $0 [make|ninja|vs]"
    exit 1
fi

# Select the appropriate generator
case "$1" in
    make)
        GENERATOR="Unix Makefiles"
        ;;
    ninja)
        GENERATOR="Ninja"
        ;;
    vs)
        GENERATOR="Visual Studio 17 2022"
        ;;
    *)
        echo "Invalid system. Use 'make', 'ninja', or 'vs'."
        exit 1
        ;;
esac


# Run CMake and build
cmake .. -G "$GENERATOR"
cmake --build .

