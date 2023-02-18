#pragma once

#include "Vector.hpp"

#include <cstdint>

class Box{
private:
    
    float _mass;
    
    Vector _pos, _initial_pos, _force, _velocity, _initial_velocity,_a, _momentum;
    
    float _width, _height, _depth;

    void computeAcc();
    void computeMomentum();
    
public:

    Box();
    Box( Vector pos, Vector velocity, Vector F, float mass, float w, float h, float d );
    
    uint64_t ID;

    void update( const float& dt );
    
    bool isColliding( Box* other );

    void print();

    void applyForce( const Vector& F );

    void handleCollision( Box* other );     

};