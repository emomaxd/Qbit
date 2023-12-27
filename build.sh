#!/bin/bash
cd src
g++ main.cpp Object.cpp Transform.cpp Component.cpp GameObject.cpp Engine.cpp Renderer.cpp Vector.cpp Scene.cpp Sphere.cpp InputHandler.cpp -L ../Dependencies/Raylib/lib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o ../build/game
cd ..
cd build/
./game
