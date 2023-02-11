#pragma once
#include "Vector.hpp"
#include "Object.hpp"

// RECTANGLE
class Box : public Object{
private:
    OBJECT_TYPE type = OBJECT_TYPE::BOX;
    float _mass;
    Vector _pos, _force, _velocity;
    float _width, _height, _depth;

public:

    Box();
    Box( Vector pos, Vector velocity, Vector F, float mass, float w, float h, float d );
    void update( const float& dt ) override ;
    bool isColliding( const Object& other ) override ;
    void applyForce( const Vector& F ) override ;

};