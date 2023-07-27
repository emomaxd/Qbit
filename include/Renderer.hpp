#pragma once

#include "../Dependencies/Raylib/include/raylib.h"
#include "Definitions.hpp"
#include "Scene.hpp"


class Renderer{

public:
    Renderer(){scene = nullptr;}
    Renderer(Scene* scene){this->scene = scene;init();}
    
    void render();

private:
    void init();
    Scene* scene;
};