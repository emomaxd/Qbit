#!/bin/bash
cd ..
cd ..
cmake -S . -B build/
cd build
make
./Qbit