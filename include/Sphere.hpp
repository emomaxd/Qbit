#pragma once

#include <memory>

#include "Object.hpp"
#include "Vector.hpp"


class Sphere : public Object
{
public:
    Sphere(const float& radius, const float& mass, const Vector& position, const Vector& rotation, const Vector& velocity);
    Sphere(const float& radius, const float& mass, const Vector& position);
    Sphere(const Sphere&);
    Sphere(const Sphere&&);
    ~Sphere();

    bool isColliding(const std::unique_ptr<Object>& other) override;
    void handleCollision(const std::unique_ptr<Object>& other) override;

    void update(const float& dt) override;

    void print() override;

private:
    float  _radius;
};
