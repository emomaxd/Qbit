#include <cstdint>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/Scene.hpp"
#include "../include/Sphere.hpp"

#include "../Dependencies/Raylib/include/raylib.h"

// FOCUSED TO SPHERE ! FIRST ! 

int main(){

    /*
    // OBJECTS INSTANTIATION
    std::unique_ptr<Object> o  = std::make_unique<Sphere>( 3, 200, Vector(0,100,0), Vector(0,0,0), Vector(0,-25.0f,0) );
    std::unique_ptr<Object> o1 = std::make_unique<Sphere>( 3, 5, Vector(0,50,0), Vector(0,0,0), Vector(0,0,0) );
    std::unique_ptr<Object> o2 = std::make_unique<Sphere>( 3, 5, Vector(0,0,0), Vector(0,0,0), Vector(0,0.0f,0));
    

    // SCENE 
    Scene* scene = Scene::getInstance();

    //Object* raw_o = o.get();
    //Object* raw_o2 = o2.get();

    //o->addForce(Vector(0, o->getMass() * -9.8f , 0));

    scene->add( std::move(o));
    scene->add( std::move(o1));
    scene->add( std::move(o2));

    scene->remove( 1 );
    
    scene->listAll();
 

    // PROGRAM LOOP
    float dt = 0;
    auto LAST_TIME = std::chrono::high_resolution_clock::now();
    
    while ( true )
    {

        scene->update( dt );
        scene->printObject((uint64_t)0, dt);


        // ---
        auto CURRENT_TIME = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration_cast< std::chrono::duration< float > >(CURRENT_TIME - LAST_TIME).count();
        // ---

        LAST_TIME = CURRENT_TIME;
    } 
    */
   
    InitWindow(800, 450, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();



    return 0;
}
