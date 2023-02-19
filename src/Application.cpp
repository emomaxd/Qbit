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
    const     float     MASS = 3;


    // OBJECTS INSTANTIATION
    std::unique_ptr<Box> b  = std::make_unique<Box>(  Vector(0,200,0), Vector(0,0,0), Vector(0, -9.8f * MASS, 0), MASS, 4, 4, 4 );
    std::unique_ptr<Box> b1 = std::make_unique<Box>( Vector(0,5,0), Vector(0,0,0), Vector(0, 0 * MASS, 0), MASS, 4, 4, 4        );
    std::unique_ptr<Box> b2 = std::make_unique<Box>( Vector(0,50,0), Vector(0,0,0), Vector(0, 0 * MASS, 0), MASS, 4, 4, 4       );
    

    // SCENE 
    Scene* scene = Scene::getInstance();

    Box* raw_b = b.get();

    scene->addBox( std::move(b) );
    scene->addBox( std::move(b1) );
    scene->addBox( std::move(b2) );

    //scene->removeBox( raw_b->ID ); // WORKS CORRECTLY!
    
    scene->listAllBoxes();
 

    // PROGRAM LOOP
    float TOTAL_TIME = 0 ;

    float dt = TARGET_DT;
    auto LAST_TIME = std::chrono::high_resolution_clock::now();
    
    while ( true )
    {
        std::cout << "Total time : " << TOTAL_TIME << "\n";
        scene->update( dt );
        raw_b->print();
        TOTAL_TIME += dt ;

        // ---
        auto CURRENT_TIME = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration_cast< std::chrono::duration< float > >(CURRENT_TIME - LAST_TIME).count();
        // ---

        // SYNCHRONIZATION WITH REAL-TIME
        LAST_TIME = CURRENT_TIME;

        float REMAINING_TIME = TARGET_DT - dt ;

        if( REMAINING_TIME > 0.0f )
            std::this_thread::sleep_for( std::chrono::duration< float > ( REMAINING_TIME ) );
        // ---
    } 
    
    return 0;
}
