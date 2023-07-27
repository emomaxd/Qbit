#include "../include/Engine.hpp"

Scene* Engine::activeScene = nullptr;

void Engine::start(){
    while ( !WindowShouldClose() )
    {
        inputHandler->listen();
        activeScene->update(1.0/GetFPS());
        renderer->render();
        
    } 
    CloseWindow();
}