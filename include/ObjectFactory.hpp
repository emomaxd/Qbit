#pragma once

#include "Sphere.hpp"
#include "Scene.hpp"

class ObjectFactory{
public:
    void createSphere(const Vector& pos, const float& mass, const float& radius);

private:
    Scene* scene;

};

