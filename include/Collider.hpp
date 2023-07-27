#pragma once

#include "Component.hpp"
#include "Vector.hpp"


class Collider : public Component {

    struct Size {
        Size() {}
        Size(float x, float y) : x(x), y(y) {}
        float x, y;
    };

public:
    Collider();
    ~Collider();

private:
    Size colliderSize;
    Vector position;
};
