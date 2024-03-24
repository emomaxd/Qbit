#pragma once

#include <glm.hpp>
#include <string>
#include <vector>


struct EntityProperties{
    bool isActive{true};

    std::string name{"GameObject"};

    std::vector<std::string> tags;
};

struct Camera{

private:
    enum class Projection {PERSPECTIVE, ORTHOGRAPHIC};

public:

    // Camera looks to origin as default
	glm::vec3 cameraTarget{0}; // position + front

	// Default camera up direction
	glm::vec3 cameraUp{ 0.0f, 1.0f, 0.0f };

	glm::vec3 cameraFront{0.0f, 0.0f, -1.0f};

	float fov = 45.0f;

    glm::vec4 clearColor{0.0f, 0.0f, 0.0f, 1.0f};

    Projection projection = Projection::PERSPECTIVE;


};


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