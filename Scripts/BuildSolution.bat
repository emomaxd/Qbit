@echo off

cd ..

cmake -DCMAKE_BUILD_TYPE=Release -S . -B .
cmake --build . --config Release

pause
