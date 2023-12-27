#pragma once

#include <glm.hpp>


struct Rigidbody{

    enum class BodyType {STATIC, DYNAMIC, KINEMATIC};


    BodyType bodyType{BodyType::STATIC};

    glm::vec3 velocity, angularVelocity;

};

struct Transform{
    glm::vec3 position{0, 0, 0}, rotation{0, 0, 0}, scale{0, 0, 0};
};

struct SphereCollider{

private:
    struct Offset{float x, y;};

public:
    Offset offset{0.0f, 0.0f};
};


