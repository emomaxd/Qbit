#include "../include/Box.hpp"


Box::Box() 
        : _force(Vector()), _pos(Vector()), _velocity(Vector()),
          _mass(0), _momentum(0,0,0), _width(0), _height(0), _depth(0), _a(0, 0, 0)   {}

Box::Box( Vector pos, Vector velocity, Vector F,
          float mass, float w, float h, float d ) 
          : _force(F), _pos(pos), _velocity(velocity),
            _mass(mass), _width(w), _height(h), _depth(d), _a(0, 0, 0), _momentum(0,0,0) {}



static float totalTimePassed = 0 ;
void Box::update( const float& dt )
{
    
    computeAcc();


    //if(isColliding())
      //  handleCollision();


    _pos = _a * totalTimePassed * totalTimePassed / 2;
    _velocity = _velocity + _a * dt ;


    computeMomentum();


    std::cout<< "Total time passed : " << totalTimePassed << "\n";


    totalTimePassed += dt;
    
}

bool Box::isColliding( const Box& other ) 
{
    return false;
}

void Box::handleCollision( const Box& other )
{
    
}

void Box::applyForce( const Vector& F )
{
    _force = _force + F;
}

void Box::computeAcc()
{
    _a = _force / _mass ; 
}

void Box::computeMomentum()
{
    _momentum = _velocity * _mass;
}

void Box::print()
{
    std::cout << "Position : " << _pos << "\nVelocity : " << _velocity << "\nAcceleration : " << _a
    << "\nMomentum : " << _momentum << "\nForce : " << _force << "\n" << std::flush;
}