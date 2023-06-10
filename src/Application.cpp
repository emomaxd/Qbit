#include <cstdint>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/Scene.hpp"
#include "../include/Sphere.hpp"

#include "../include/InputHandler.hpp"

#include "../Dependencies/Raylib/include/raylib.h"

// FOCUSED TO SPHERE ! FIRST ! 

void DrawMenu(int objectCount)
{
    // Draw menu elements
    const char* text = "Object Count: " + objectCount;
    //std::cout << " TEXT : " << text << " ";
    DrawText("Menu", 10, 10, 20, BLACK);
    DrawText(text, 10, 40, 16, BLACK);
}


int main(){

    int radius = 30;
    // OBJECTS INSTANTIATION
    //std::unique_ptr<Object> o  = std::make_unique<Sphere>( radius, 5, Vector(400,-50,0), Vector(0,0,0), Vector(0,-30.0f,0) );
    //std::unique_ptr<Object> o1 = std::make_unique<Sphere>( radius, 5, Vector(400,50,0), Vector(0,0,0), Vector(0,0,0) );
    //std::unique_ptr<Object> o2 = std::make_unique<Sphere>( radius, 5, Vector(400,-200,0), Vector(0,0,0), Vector(0,0,0) );
    

    // SCENE 
    Scene* scene = Scene::getInstance();
    InputHandler* inputHandler = InputHandler::getInstance();

    //Object* raw_o = o.get();
    //Object* raw_o2 = o2.get();

    //scene->add( std::move(o));
    //scene->add( std::move(o1));
    //scene->add( std::move(o2));

    //scene->remove( 1 );
    
    scene->listAll();
 
    InitWindow(800, 450, "raylib [core] example - basic window");

    // PROGRAM LOOP
    float dt = 0;
    auto LAST_TIME = std::chrono::high_resolution_clock::now();

    

    
    while ( !WindowShouldClose() )
    {

        std::thread([&scene](double dt) {
            scene->update(dt);
            //scene->printObject((uint64_t)0, dt);
        }, dt).detach();

     



        // ---
        auto CURRENT_TIME = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration_cast< std::chrono::duration< float > >(CURRENT_TIME - LAST_TIME).count();
        // ---

        LAST_TIME = CURRENT_TIME;

        //std::cout << "FPS : " << 1.0 / dt << std::endl;
        //std::cout<< "RAW O POS : " <<raw_o->getPosition().getY() << std::endl;
            

            inputHandler->listen();
            const std::vector<std::unique_ptr<Object>>& v = scene->getObjects();
            

            BeginDrawing();
                ClearBackground(RAYWHITE);

                for(auto& s : v)
                    DrawCircle(s.get()->getPosition().getX(), s.get()->getPosition().getY(), radius, RED);    

                //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
                //DrawCircle(400+raw_o->getPosition().getX(), 225 -raw_o->getPosition().getY(), radius, RED);
                //DrawCircle(400+raw_o2->getPosition().getX(), 225 -raw_o2->getPosition().getY(), radius, RED);

            EndDrawing();
        
    } 
    
   
    

    

    CloseWindow();



    return 0;
}
