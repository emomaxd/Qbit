@echo off
mkdir build
cmake -S . -B /build -G "MinGW Makefiles"
mingw32-make 
build\game.exe
pause
