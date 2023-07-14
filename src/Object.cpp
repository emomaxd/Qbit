
#include "../include/Object.hpp"


uint64_t Object::count = 0;

Object::Object(float  mass, Vector position){
    
}

Object::~Object() {}

void Object::addForce(const Vector& F) {
    _netForce += F;
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
