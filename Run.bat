@echo off

REM Configure CMake for release build
cmake -S . -B . -DCMAKE_BUILD_TYPE=Release

REM Build the project
cmake --build . --config Release

REM Run the executable
.\Qbit.exe

REM Pause to keep the console window open
pause
