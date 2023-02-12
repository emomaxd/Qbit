#pragma once
#include "Vector.hpp"

// RECTANGLE
class Box{
private:
    
    float _mass;
    
    Vector _pos, _force, _velocity, _a;
    
    float _width, _height, _depth;
    
public:

    Box();
    Box( Vector pos, Vector velocity, Vector F, float mass, float w, float h, float d );
    
    
    void update( const float& dt );
    
    bool isColliding( const Box& other );
    
    void applyForce( const Vector& F );
    void computeAcc();

};