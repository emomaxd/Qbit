#include "../include/Box.hpp"

Box::Box() 
        : _force(Vector()), _pos(Vector()), _velocity(Vector()),
          _mass(0), _width(0), _height(0), _depth(0), _a(0, 0, 0)   {}

Box::Box( Vector pos, Vector velocity, Vector F,
          float mass, float w, float h, float d ) 
          : _force(F), _pos(pos), _velocity(velocity),
            _mass(mass), _width(w), _height(h), _depth(d), _a(0, 0, 0) {}


void Box::update( const float& dt )
{
    // dt will be 1.0f / 60.0f 
    //            1 sec / 60 frame rate(FPS)
    //will be inside the game loop
    //and also there will be a object pool with OBSERVER design
    
    computeAcc();
    
    _velocity = _velocity + _a * dt ;
    
    _pos =  _velocity * dt ;
}

bool Box::isColliding( const Box& other) 
{
    return false;
}

void Box::applyForce( const Vector& F )
{
    _force = _force + F;
}

void Box::computeAcc()
{
    _a = _force / _mass ; 
}