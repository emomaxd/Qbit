#pragma once
#include "../Dependencies/Raylib/include/raylib.h"


#include "ObjectFactory.hpp"




class InputHandler{
public:

    static InputHandler* getInstance();

    void listen();
   


private:

    static InputHandler* _instance;

    InputHandler(){} 
    ~InputHandler() = default;

};