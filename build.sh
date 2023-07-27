#!/bin/bash
cd src
g++ main.cpp Object.cpp Engine.cpp Renderer.cpp Vector.cpp Scene.cpp Sphere.cpp InputHandler.cpp -L ../Dependencies/Raylib/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -o ../build/game.exe
cd ..
cd build/
./game.exe
