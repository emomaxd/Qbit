#pragma once

#include "../Dependencies/Raylib/include/raylib.h"

#include "Vector.hpp"


class InputHandler{
public:

    static InputHandler* getInstance();

    void listen();
   


private:

    static InputHandler* _instance;

    InputHandler(){} 
    ~InputHandler() = default;

    void createSphereWithVelocity(Vector velocity, int radius, int mass);
};