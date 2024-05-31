#!/bin/bash

# Navigate to the GLFW source directory
GLFW_SOURCE_DIR="../Vendor/glfw"
cd "$GLFW_SOURCE_DIR" || exit

# Run CMake to configure the build
cmake -S . -B build -DCMAKE_INSTALL_PREFIX="$PWD/install"

# Build GLFW using make
cmake --build build --config Release --target install
