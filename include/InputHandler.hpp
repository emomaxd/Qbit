#pragma once
#include "../Dependencies/Raylib/include/raylib.h"

#include "ObjectFactory.hpp"




class InputHandler{
public:
    static InputHandler* getInstance(){if(!_instance) return new InputHandler(); return _instance;}
    void listen();
    ~InputHandler(){
        delete this;
    }


private:

    static InputHandler* _instance;
    InputHandler(){}

};