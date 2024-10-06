@echo off

:: =========================
:: Section 1: Update Git Submodules
:: =========================

echo Updating git submodules...

:: Navigate to the root directory (if necessary)
cd ..

:: Update submodules recursively
call git submodule update --init --recursive

:: Navigate back to the project directory
cd Engine/vendor

:: =========================
:: Section 2: Build GLFW
:: =========================

echo Building GLFW...

:: Navigate to the GLFW source directory
cd glfw

:: Run CMake to configure the build
call cmake -S . -B build

:: Build GLFW Debug configuration
echo Building GLFW Debug...
call cmake --build build/ --config Debug

:: Clear screen and prompt for Release build
call cls

:: Build GLFW Release configuration
echo Building GLFW Release...
call cmake --build build/ --config Release

:: Navigate back to the vendor directory
cd ..

:: =========================
:: Section 3: Build Assimp
:: =========================

echo Building Assimp...

:: Navigate to the Assimp vendor directory
cd assimp

:: Run CMake to configure Assimp for both Debug and Release builds
call cmake -S . -B build -DASSIMP_BUILD_ZLIB=ON -DBUILD_SHARED_LIBS=OFF

:: Build Assimp Debug configuration
echo Building Assimp Debug...
call cmake --build build --config Debug

:: Build Assimp Release configuration
echo Building Assimp Release...
call cmake --build build --config Release

echo Build process complete!
pause
