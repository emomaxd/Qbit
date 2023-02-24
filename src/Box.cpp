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
    
    _a = _force * _mass;

    if( _a.getMagnitude() != 0){
        _pos = _pos + _velocity * dt + _a * dt * dt * 0.5f;
        _velocity = _velocity + _a * dt;
    }

    if( _velocity.getMagnitude() != 0)
        _momentum = _velocity * _mass;
    
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

void Box::handleCollision( const std::unique_ptr<Box>& other )
{
    Box* otherP = other.get();

    float k1 = 0.5f * _mass * pow(_velocity.getMagnitude(), 2);
    float k2 = 0.5f * otherP->_mass * pow(otherP->_velocity.getMagnitude(), 2); 
    float E = k1 + k2;

    Vector v1f = _velocity - (otherP->_mass / (otherP->_mass + _mass) ) * (_velocity - otherP->_velocity) + (2 * otherP->_mass / (otherP->_mass + _mass) ) * (otherP->_velocity - _velocity);
    _velocity = v1f;
}

void Box::addForce( const Vector& F )
{
    _force = _force + F;
}

void Box::removeForce( const Vector& F )
{
    _force = _force - F;
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