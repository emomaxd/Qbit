@echo off
cmake . -G "MinGW Makefiles"
mingw32-make 
build\game.exe
pause
