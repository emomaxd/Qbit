@echo off
mkdir build
cd src
g++ Application.cpp Vector.cpp Box.cpp Scene.cpp Sphere.cpp -o ..\build\O.exe
cd ..
build\O.exe