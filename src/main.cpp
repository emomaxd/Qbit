#include <cstdint>
#include <iostream>

#include "../include/Definitions.hpp"

#include "../include/Engine.hpp"

#include "../include/GameObject.hpp"

#include "../include/Transform.hpp"

//
int TARGET_FPS = 60;
int WIDTH = 800;
int HEIGHT = 450;
//
int main(){
    
    /// INITIAL SCENE
    Scene scene;
    
    /// ONLY RENDERER ON THE PROGRAM TIME
    Renderer renderer(&scene);

    /// THE PROGRAM ITSELF
    Engine engine(&renderer, &scene);
    
    /// FIX THIS FUNCTION
    //scene->getObject((uint64_t)0);


    /// DOUBLE FREE WARNING ON LINUX !?!?
    
    GameObject g1;

    g1.AddComponent<cTransform>();




    engine.start();


    return 0;
}
