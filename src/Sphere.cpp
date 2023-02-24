#include <cmath>
#include <iostream>

#include "../include/Sphere.hpp"

Sphere::Sphere(const float& radius, const float& mass, const Vector& position, const Vector& velocity)
    : _radius(radius)
{
    _mass = mass;
    _position = position;
    _velocity = velocity;
    TYPE = 0;
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
            std::cout << "Collided with another sphere" << std::endl;
            exit(0);
            return true;
        }
    }

    // NON-SPHERE COLLISION CHECK
    /*
        // IMPLEMENTATION
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

    Vector v1f = _velocity - (otherP->_mass / (otherP->_mass + _mass) ) * (_velocity - otherP->_velocity) + (2 * otherP->_mass / (otherP->_mass + _mass) ) * (otherP->_velocity - _velocity);
    _velocity = v1f;
}

void Sphere::update(const float& dt)
{
    Vector acceleration = calcAcceleration(_netForce, _mass);
    _velocity = _velocity + acceleration * dt;
    _position = _position + _velocity * dt;
}

void Sphere::print()
{
    std::cout << "Sphere: radius = " << _radius << ", mass = " << _mass << ", position = (" << _position.getX() << ", " << _position.getY() << ", " << _position.getZ() << ")" << std::endl;
}