@echo off

:: Navigate to the GLFW source directory
cd ../../Engine/vendor/glfw

:: Run CMake to configure the build
cmake -S . -B build -DCMAKE_INSTALL_PREFIX="install/"

:: Build GLFW using make
cmake --build build --config Release --target install