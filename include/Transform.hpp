#pragma once

#include "Component.hpp"
#include "Vector.hpp"

#include "GameObject.hpp"

/// RENAME THIS CLASS AS "Transform" after remove the raylib from the project

class cTransform : public Component {

public:
    cTransform(){
        name = "Transform";       
    }
    Vector position{};
    Vector rotation{};
};