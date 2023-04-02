#include <iostream>

#include "../include/Object.hpp"


uint64_t Object::count = 0;

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
