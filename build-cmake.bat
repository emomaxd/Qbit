@echo off
cmake . -G "MinGW Makefiles"
mingw32-make .
build\Physics.exe

# HAVEN'T TESTED YET