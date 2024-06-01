@echo off
cd ..
cd ..
mkdir build
cmake -S . -B build/
cd build
::cmake --build .
pause
