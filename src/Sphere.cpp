#include "../include/Sphere.hpp"


Sphere::Sphere(const float& radius, const float& mass, const Vector& position)
    : _radius(radius)
{
    _mass = mass;
    _position = position;
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

        float distance = (_position - otherSphere->_position).getMagnitude();

        float sumRadii = _radius + otherSphere->_radius;

        if (distance < sumRadii) {
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

        Vector centersVector = _position - otherP->_position;
        centersVector = centersVector.normalized();

        Vector v1proj = dotProduct(v1i, centersVector) * centersVector;
        Vector v2proj = dotProduct(v2i, centersVector) * centersVector;

        float v1n = -1.0f * v1proj.getMagnitude();
        float v2n = v2proj.getMagnitude();

        float v1n_final = (v1n * (this->_mass - otherP->_mass) + 2 * otherP->_mass * v2n) / (this->_mass + otherP->_mass);
        float v2n_final = (v2n * (otherP->_mass - this->_mass) + 2 * this->_mass * v1n) / (this->_mass + otherP->_mass);

        _velocity         = (v1i - v1proj) + (v1n_final * centersVector);
        otherP->_velocity = (v2i - v2proj) + (v2n_final * centersVector);

}

void Sphere::update(const float& dt) 
{

    boundaryCollision(WIDTH, HEIGHT, this);

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

void Sphere::boundaryCollision(uint32_t WIDTH,uint32_t HEIGHT, Sphere* sphere){

    if(sphere->_position.getX() - sphere->_radius <= 0 || sphere->_position.getX() + sphere->_radius >= WIDTH)
        sphere->_velocity.setX(-1*sphere->_velocity.getX());

    if(sphere->_position.getY() - sphere->_radius <= 0 || sphere->_position.getY() + sphere->_radius >= HEIGHT)
        sphere->_velocity.setY(-1*sphere->_velocity.getY());
}

