#pragma once

#include "key_codes.h"
#include "mouse_codes.h"

#include <glm/glm.hpp>

namespace Qbit {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}