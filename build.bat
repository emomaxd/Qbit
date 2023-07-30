@echo off

cd src
g++ main.cpp Object.cpp Transform.cpp Component.cpp GameObject.cpp Engine.cpp Renderer.cpp Vector.cpp Scene.cpp Sphere.cpp InputHandler.cpp -L ../Dependencies/Raylib/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -o ../build/game.exe
cd ..
.\build\game.exe
