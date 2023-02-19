#include "../include/Box.hpp"


Box::Box() 
        : _force(Vector()), _pos(Vector()), _velocity(Vector()),
          _mass(0), _momentum(0,0,0), _width(0), _height(0), _depth(0), _a(0, 0, 0) {}

Box::Box( Vector pos, Vector velocity, Vector F,
          float mass, float w, float h, float d ) 
          : _pos(pos), _velocity(velocity), _force(F),
            _mass(mass), _width(w), _height(h), _depth(d) , _a(0,0,0), _momentum(0,0,0) {}

Box::~Box()
{
    std::cout << "Destructor called, Object " << ID << " deleted\n";
}

void Box::update( const float& dt )
{
    
    computeAcc();

    if( _a.getMagnitude() != 0){
        _pos = _pos + _velocity * dt + _a * dt * dt * 0.5f;
        _velocity = _velocity + _a * dt;
    }

    if( _velocity.getMagnitude() != 0)
        computeMomentum();
    
}

bool Box::isColliding( const std::unique_ptr<Box>& other ) 
{

    Vector thisMinCorner = _pos - Vector( _width / 2.0f, _height / 2.0f, _depth / 2.0f );
    Vector thisMaxCorner = _pos + Vector( _width / 2.0f, _height / 2.0f, _depth / 2.0f );

    Vector otherMinCorner = other->_pos - Vector( other->_width / 2.0f, other->_height / 2.0f, other->_depth / 2.0f );
    Vector otherMaxCorner = other->_pos + Vector( other->_width / 2.0f, other->_height / 2.0f, other->_depth / 2.0f );

    // X - axis
    if( thisMaxCorner.getX() < otherMinCorner.getX() || thisMinCorner.getX() > otherMaxCorner.getX() )
        return false;
    
    // Y - axis
    if( thisMaxCorner.getY() < otherMinCorner.getY() || thisMinCorner.getY() > otherMaxCorner.getY() )
        return false;

    // Z - axis
    if( thisMaxCorner.getZ() < otherMinCorner.getZ() || thisMinCorner.getZ() > otherMaxCorner.getZ() )
        return false;
    
    return true;
}

// 3D - GENERALIZED MOMENTUM CALCULATION FOR BOXES THEIR CENTER IS NOT ALIGNED , CALCULATE TORQUE ALSO
void Box::handleCollision( const std::unique_ptr<Box>& other )
{
    std::cout << "Collision handled!\n";
    Vector distance = other->_pos - _pos;

    Vector unit_normal = distance.normalized();
    //Vector unit_tangent = Vector(-unit_normal.getY(), -unit_normal.getX());


}

void Box::addForce( const Vector& F )
{
    _force = _force + F;
}

void Box::removeForce( const Vector& F )
{
    _force = _force - F;
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
    std::cout << "Position     : "   << _pos << 
                 "\nVelocity     : " << _velocity << 
                 "\nAcceleration : " << _a << 
                 "\nMomentum     : " << _momentum << 
                 "\nForce        : " << _force << 
    "\n";
}


// GETTER SETTER

Vector Box::getPos(){ return _pos; }