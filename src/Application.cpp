#include <cstdint>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/Vector.hpp"
#include "../include/Box.hpp"
#include "../include/Scene.hpp"


int main(){


    // PROGRAM DECLERATIONS 
    const     uint8_t   TARGET_FPS = 60 ;
    constexpr float     TARGET_DT  = 1.0f / TARGET_FPS ;


    // OBJECT PROPERTIES
    const     float     MASS = 5;


    // OBJECTS INSTANTIATION
    Box b( Vector(0,0,0), Vector(0,0,0), Vector(0, -9.8f * MASS, 0), MASS, 4, 4, 4 );
    

    // SCENE 
    Scene* scene = Scene::getInstance();
    b.ID = scene->addBox( &b );


    // PROGRAM LOOP
    auto LAST_TIME = std::chrono::high_resolution_clock::now();

    float i = 0 ;
    while ( true )
    {


        //
        auto CURRENT_TIME = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration_cast<std::chrono::duration<float>>(CURRENT_TIME - LAST_TIME).count();
        //


        scene->update( dt );
        b.print();

        i += dt ;

        // SYNCHRONIZATION WITH REAL-TIME
        LAST_TIME = CURRENT_TIME;

        float REMAINING_TIME = TARGET_DT - dt ;

        if( REMAINING_TIME > 0.0f )
            std::this_thread::sleep_for( std::chrono::duration< float > ( REMAINING_TIME ) );
        //
    } 

    
    std::cin.get();
    return 0;


}
