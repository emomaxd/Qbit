#pragma once

#include <memory>
#include <cmath>
#include <iostream>

#include "Object.hpp"
#include "Vector.hpp"
#include "Definitions.hpp"


class Sphere : public Object
{
public:
    Sphere();
    Sphere(const float& radius, const float& mass, const Vector& position);
    Sphere(const Sphere&);
    ~Sphere();

    bool isColliding(const std::unique_ptr<Object>& other) override;
    void handleCollision(const std::unique_ptr<Object>& other) override;

    void update(const float& dt) override;

    void print() override;

    void setRadius(float radius){_radius = radius;}
    float getRadius() const {return _radius;}

private:
    float  _radius;
};
