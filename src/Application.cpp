#include <cstdint>
#include <iostream>

#include "../include/Scene.hpp"
#include "../include/Sphere.hpp"

#include "../include/InputHandler.hpp"

#include "../Dependencies/Raylib/include/raylib.h"

#include "../include/Definitions.hpp"


//
int TARGET_FPS = 60;
int WIDTH = 800;
int HEIGHT = 450;
//
int main(){

    Scene* scene = Scene::getInstance();
    InputHandler* inputHandler = InputHandler::getInstance();
    
    scene->listAll();
 
    InitWindow(WIDTH, HEIGHT, "Physic Engine");
    SetTargetFPS(TARGET_FPS);

    int FPS; 
    float dt = 0;

    
    while ( !WindowShouldClose() )
    {
        FPS = GetFPS();
        dt = 1.0 / FPS;


        inputHandler->listen();
        scene->update(dt);
        
        

     

        //std::cout << "FPS : " << FPS << std::endl;
            

        
        const std::vector<std::unique_ptr<Object>>& v = scene->getObjects();
            

        BeginDrawing();
            ClearBackground(RAYWHITE);

            for(auto& s : v)
                DrawCircle(s.get()->getPosition().getX(), s.get()->getPosition().getY(), dynamic_cast<Sphere*>(s.get())->getRadius(), RED);   
                 

        EndDrawing();
        
    } 
    CloseWindow();
    return 0;
}
