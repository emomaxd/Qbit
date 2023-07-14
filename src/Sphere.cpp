#include "../include/Sphere.hpp"

#include "../Dependencies/glm/gtx/projection.hpp"
//#include <../Dependencies/glm/gtx/perpendicular.hpp>

#include "../Dependencies/glm/vec3.hpp"



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

Sphere::~Sphere()
{
    std::cout << "Destructor called, SPHERE " << ID << " deleted\n";
    count--;
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
        


        glm::vec3 v1i = glm::vec3(this->_velocity.getX(), this->_velocity.getY(), this->_velocity.getZ());

        glm::vec3 v2i = glm::vec3(otherP->_velocity.getX(), otherP->_velocity.getY(), otherP->_velocity.getZ());

    
        // Calculate centersVector
        glm::vec3 centersVector = glm::vec3(
            this->_position.getX() - otherP->_position.getX(),
            this->_position.getY() - otherP->_position.getY(),
            this->_position.getZ() - otherP->_position.getZ()
        );

        centersVector = glm::normalize(centersVector);

        // Calculate projections
        glm::vec3 v1proj = glm::dot(v1i, centersVector) * centersVector;
        glm::vec3 v2proj = glm::dot(v2i, centersVector) * centersVector;

        // Calculate normal velocities
        float v1n = -1.0f * glm::length(v1proj);
        float v2n = glm::length(v2proj);

        // Calculate final normal velocities after collision
        float v1n_final = (v1n * (this->_mass - otherP->_mass) + 2 * otherP->_mass * v2n) / (this->_mass + otherP->_mass);
        float v2n_final = (v2n * (otherP->_mass - this->_mass) + 2 * this->_mass * v1n) / (this->_mass + otherP->_mass);

        // Calculate final velocities
        glm::vec3 v1f = (v1i - v1proj) + (v1n_final * centersVector);
        glm::vec3 v2f = (v2i - v2proj) + (v2n_final * centersVector);

        // Update velocities
        this->_velocity = Vector(v1f.x, v1f.y, v1f.z);
        otherP->_velocity = Vector(v2f.x, v2f.y, v2f.z);

}

void Sphere::update(const float& dt) 
{
    Vector acceleration = calcAcceleration(_netForce, _mass);
    
    if(acceleration.getMagnitude() != 0)
        _velocity += acceleration * dt;

    if(_position.getX() - _radius <= 0 || _position.getX() + _radius >= WIDTH)
        _velocity.setX(-1*_velocity.getX());

    if(_position.getY() - _radius <= 0 || _position.getY() + _radius >= HEIGHT)
        _velocity.setY(-1*_velocity.getY());

    _position += _velocity * dt;
}

void Sphere::print()
{
    std::cout << "\rSphere: radius = " << _radius << ", mass = " << _mass << ", position = (" << _position.getX() << ", " << _position.getY() << ", " << _position.getZ() << ")"
    << "Sphere: velocity = " << _velocity << "\n";
}

