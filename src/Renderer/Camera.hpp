#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

const static float NEAR = 1.0f, FAR = 100.0f;
const static float WIDTH = 800, HEIGHT = 800;

class Camera {
public:
	Camera() = default;
	

	// Initial position will be at 0, 0, 5.0f (Outward to the screen)
	glm::vec3 cameraPosition{0, 0, 5.0f};

	// Camera looks to origin as default
	glm::vec3 cameraTarget{0};

	// Default camera up direction
	glm::vec3 cameraUp{ 0.0f, 1.0f, 0.0f };
	

	glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
};