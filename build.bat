@echo off
cd src
g++ Application.cpp Vector.cpp Box.cpp -o ..\build\a.exe
cd ..
build\a.exe
