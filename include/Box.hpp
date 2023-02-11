#pragma once
#include "Vector.hpp"
#include "Object.hpp"

// RECTANGLE
class Box : public Object{
private:

    Vector velocity;
    Vector position;
    Vector net_force;
    
    float width, height, depth;
    float mass;

public:

    Box();
    Box( Vector pos, Vector velocity, Vector F, float mass, float w, float h, float d );
    void Update();

};