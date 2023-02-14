#pragma once

#include "Vector.hpp"

#include <cstdint>

class Box{
private:
    
    float _mass;
    
    Vector _pos, _force, _velocity, _a, _momentum;
    
    float _width, _height, _depth;

    void computeAcc();
    void computeMomentum();
    
public:

    Box();
    Box( Vector pos, Vector velocity, Vector F, float mass, float w, float h, float d );
    
    uint64_t ID;

    void update( const float& dt );
    
    bool isColliding( const Box& other );

    void print();


    void applyForce( const Vector& F );

    void handleCollision( const Box& other );     

};