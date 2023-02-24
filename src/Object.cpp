#include <iostream>

#include "../include/Object.hpp"


Object::~Object() {}

void Object::addForce(const Vector& F) {
    _netForce += F;
}

void Object::addForce(const Vector& F, const Vector& applyPosition) {
    // TO-DO
}

void Object::removeForce(const Vector& F) {
    _netForce -= F;
}

Vector Object::calcAcceleration(const Vector& F, const float& mass) const {
    return F / mass;
}

Vector Object::calcMomentum(const Vector& V, const float& mass) const {
    return V * mass;
}

void Object::print() {
    std::cout << "Object ID: " << ID << std::endl;
    std::cout << "Mass: " << _mass << std::endl;
    std::cout << "Position: (" << _position.getX() << ", " << _position.getY() << ", " << _position.getZ() << ")" << std::endl;
    std::cout << "Velocity: (" << _velocity.getX() << ", " << _velocity.getY() << ", " << _velocity.getZ() << ")" << std::endl;
    std::cout << "Net force: (" << _netForce.getX() << ", " << _netForce.getY() << ", " << _netForce.getZ() << ")" << std::endl;
}
