@echo off
mkdir build
cd src
g++ -DGLEW_STATIC Core/EntryPoint.cpp Core/Window.cpp Core/Engine.cpp Renderer/Renderer.cpp Renderer/IndexBuffer.cpp Renderer/Shader.cpp Renderer/VertexArray.cpp Renderer/VertexBuffer.cpp Scene/Scene.cpp System/Physic.cpp -I ../Dependencies/glm -I ../Dependencies/GLFW/include -I ../Dependencies/GLEW/include  -L ../Dependencies/GLFW/lib-mingw-w64/ -L ../Dependencies/GLEW/lib/Release/x64 -lglew32s -lglfw3 -lopengl32 -lgdi32 -lwinmm -o ../build/game.exe
cd ..
.\build\game.exe
pause
