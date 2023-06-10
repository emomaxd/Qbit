@echo off

cd src
g++ Application.cpp Object.cpp Vector.cpp Box.cpp Scene.cpp Sphere.cpp InputHandler.cpp ObjectFactory.cpp -L ../Dependencies/Raylib/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -o ../build/game.exe
cd ..
.\build\game.exe
