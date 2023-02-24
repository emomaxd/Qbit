#include <cstdint>
#include <iostream>
#include <chrono>
#include <thread>

#include "../include/Scene.hpp"
#include "../include/Sphere.hpp"

// FOCUSED TO SPHERE ! FIRST ! 

int main(){


    // PROGRAM DECLERATIONS 
    const     uint8_t   TARGET_FPS = 60 ;
    constexpr float     TARGET_DT  = 1.0f / TARGET_FPS ;


    // OBJECTS INSTANTIATION
    std::unique_ptr<Object> o  = std::make_unique<Sphere>( 3, 5, Vector(0,200,0), Vector(0,0,0) );
    std::unique_ptr<Object> o1 = std::make_unique<Sphere>( 3, 5, Vector(0,50,0), Vector(0,0,0) );
    std::unique_ptr<Object> o2 = std::make_unique<Sphere>( 3, 5, Vector(0,5,0), Vector(0,0,0));
    

    // SCENE 
    Scene* scene = Scene::getInstance();

    Object* raw_o = o.get();

    o->addForce(Vector(0, o->getMass() * -9.8f , 0));

    o->setID(scene->add( std::move(o)));
    o1->setID(scene->add( std::move(o1)));
    o2->setID(scene->add( std::move(o2)));


    scene->remove( 1 );
    
    scene->listAll();
 

    // PROGRAM LOOP
    float TOTAL_TIME = 0 ;

    float dt = TARGET_DT;
    auto LAST_TIME = std::chrono::high_resolution_clock::now();
    
    while ( true )
    {
        std::cout << "Total time : " << TOTAL_TIME << "\n";
        scene->update( dt );
        raw_o->print();
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
