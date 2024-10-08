@echo off

:: =========================
:: Section 1: Update Git Submodules
:: =========================

:: Set text to light green on black for info messages
color 0A
echo ==============================================================
echo.
echo  [INFO] Updating Git Submodules...
echo.
echo ==============================================================
:: Navigate to the root directory (if necessary)
cd ..

:: Update submodules recursively
call git submodule update --init --recursive
:: Check for errors after updating git submodules
if ERRORLEVEL 1 (
    color 0C
    echo ==============================================================
    echo.
    echo  [ERROR] Failed to update Git submodules!
    echo  Please check your Git configuration or repository.
    echo.
    echo ==============================================================
    pause
    exit /b
)

:: Navigate back to the project directory
cd Engine/vendor

:: =========================
:: Section 2: Build GLFW
:: =========================
cls
color 0B
echo ==============================================================
echo.
echo  [BUILD] Building GLFW...
echo.
echo ==============================================================
timeout /t 2 /nobreak

:: Navigate to the GLFW source directory
cd glfw

:: Run CMake to configure the build
call cmake -S . -B build
if ERRORLEVEL 1 (
    color 0C
    echo ==============================================================
    echo.
    echo  [ERROR] CMake configuration failed for GLFW!
    echo  Check the CMake output for issues.
    echo.
    echo ==============================================================
    pause
    exit /b
)

:: Build GLFW Debug configuration
cls
echo ==============================================================
echo.
echo  [BUILD] Building GLFW Debug Configuration...
echo.
echo ==============================================================
timeout /t 2 /nobreak
call cmake --build build/ --config Debug
if ERRORLEVEL 1 (
    color 0C
    echo ==============================================================
    echo.
    echo  [ERROR] Failed to build GLFW Debug configuration!
    echo.
    echo ==============================================================
    pause
    exit /b
)

:: Build GLFW Release configuration
cls
echo ==============================================================
echo.
echo  [BUILD] Building GLFW Release Configuration...
echo.
echo ==============================================================
timeout /t 2 /nobreak
call cmake --build build/ --config Release
if ERRORLEVEL 1 (
    color 0C
    echo ==============================================================
    echo.
    echo  [ERROR] Failed to build GLFW Release configuration!
    echo.
    echo ==============================================================
    pause
    exit /b
)

:: Navigate back to the vendor directory
cd ..

:: =========================
:: Section 3: Build Assimp
:: =========================
cls
color 0D
echo ==============================================================
echo.
echo  [BUILD] Building Assimp...
echo.
echo ==============================================================
timeout /t 2 /nobreak

:: Navigate to the Assimp vendor directory
cd assimp

:: Run CMake to configure Assimp for both Debug and Release builds
call cmake -S . -B build -DASSIMP_BUILD_ZLIB=ON -DBUILD_SHARED_LIBS=OFF
if ERRORLEVEL 1 (
    color 0C
    echo ==============================================================
    echo.
    echo  [ERROR] CMake configuration failed for Assimp!
    echo.
    echo ==============================================================
    pause
    exit /b
)

:: Build Assimp Debug configuration
cls
echo ==============================================================
echo.
echo  [BUILD] Building Assimp Debug Configuration...
echo.
echo ==============================================================
timeout /t 2 /nobreak
call cmake --build build --config Debug
if ERRORLEVEL 1 (
    color 0C
    echo ==============================================================
    echo.
    echo  [ERROR] Failed to build Assimp Debug configuration!
    echo.
    echo ==============================================================
    pause
    exit /b
)

:: Build Assimp Release configuration
cls
echo ==============================================================
echo.
echo  [BUILD] Building Assimp Release Configuration...
echo.
echo ==============================================================
timeout /t 2 /nobreak
call cmake --build build --config Release
if ERRORLEVEL 1 (
    color 0C
    echo ==============================================================
    echo.
    echo  [ERROR] Failed to build Assimp Release configuration!
    echo.
    echo ==============================================================
    pause
    exit /b
)

:: Set text to light yellow for the final success message
color 0E
cls
echo ==============================================================
echo.
echo  [INFO] Build process complete with no errors!
echo.
echo ==============================================================
pause
