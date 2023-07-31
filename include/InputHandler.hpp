#pragma once

#include "../Dependencies/Raylib/include/raylib.h"

#include "Vector.hpp"


class InputHandler{
public:

    static InputHandler* getInstance();

    void listen();
   
    ~InputHandler(){
        delete _instance;
        _instance=nullptr;
    }

private:

    static InputHandler* _instance;

    InputHandler(){} 

    void createSphereWithVelocity(Vector velocity, int radius, int mass);
};