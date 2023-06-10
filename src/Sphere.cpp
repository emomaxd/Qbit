#include <cmath>
#include <iostream>

#include "../include/Sphere.hpp"

Sphere::Sphere(const float& radius, const float& mass, const Vector& position, const Vector& rotation, const Vector& velocity)
    : _radius(radius)
{
    _mass = mass;
    _position = position;
    _velocity = velocity;
    _rotation = rotation;
    ID = count++;
}

Sphere::Sphere(const float& radius, const float& mass, const Vector& position)
    : _radius(radius)
{
    _mass = mass;
    _position = position;
    ID = count++;
}

Sphere::Sphere(const Sphere& sp){
    _mass = sp._mass;
    _position = sp._position;
    _radius = sp._radius;
    _velocity = sp._velocity;
    ID = count++;
}

Sphere::Sphere(const Sphere&& sp){
    std::cout << "R - VALUE CONSTR. SPHERE";
}

Sphere::~Sphere()
{
    std::cout << "Destructor called, SPHERE " << ID << " deleted\n";
}

bool Sphere::isColliding(const std::unique_ptr<Object>& other)
{
    Sphere* otherSphere = dynamic_cast<Sphere*>(other.get());
    if (otherSphere != nullptr) {
        // Calculate the distance between the centers of the two spheres
        float distance = (_position - otherSphere->_position).getMagnitude();

        // Calculate the sum of the radii of the two spheres
        float sumRadii = _radius + otherSphere->_radius;

        // If the distance between the centers is less than the sum of the radii,
        // the two spheres are colliding
        if (distance < sumRadii) {
            //std::cout << "\nCollided with another sphere";
            return true;
        }
    }

    // NON-SPHERE COLLISION CHECK
    /*
    *  IMPLEMENTATION
    */

    return false;
}

void Sphere::handleCollision(const std::unique_ptr<Object>& other)
{
    Sphere* otherP = dynamic_cast<Sphere*>(other.get());
    if (otherP == nullptr) {
        // handle collision with non-Sphere object
        return;
    }
    Vector v1i = _velocity;
    Vector v2i = otherP->_velocity;

    // v1 final
    _velocity = ((v1i * (_mass - otherP->_mass )) + 2.0f * otherP->_mass * v2i) / (_mass + otherP->_mass);
    
    // v2 final
    otherP->_velocity = ((v2i * (otherP->_mass - _mass )) + 2.0f * _mass * v1i) / (_mass + otherP->_mass);
    
}

void Sphere::update(const float& dt) 
{
    Vector acceleration = calcAcceleration(_netForce, _mass);
    
    if(acceleration.getMagnitude() != 0)
        _velocity += acceleration * dt;

        _position += _velocity * dt;
}

void Sphere::print()
{
    std::cout << "\rSphere: radius = " << _radius << ", mass = " << _mass << ", position = (" << _position.getX() << ", " << _position.getY() << ", " << _position.getZ() << ")"
    << "Sphere: velocity = " << _velocity << "\n";
}

