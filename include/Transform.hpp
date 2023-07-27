#pragma once

#include "Component.hpp"
#include "GameObject.hpp"
#include "Vector.hpp"

class Transform : public Component {

public:
    GameObject* gameObject;
    Vector position;
    Vector rotation;
};