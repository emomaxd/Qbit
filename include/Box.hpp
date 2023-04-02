#pragma once

#include <memory>

#include "Object.hpp"
#include "Vector.hpp"

// SUSPENDED

class Box : public Object
{
public:
    Box(const float& radius, const float& mass, const Vector& position, const Vector& rotation, const Vector& velocity);
    ~Box();

    bool isColliding(const std::unique_ptr<Object>& other) override;
    void handleCollision(const std::unique_ptr<Object>& other) override;

    void update(const float& dt) override;

    void print() override;

private:
    float  _width, _height, _depth;
};
