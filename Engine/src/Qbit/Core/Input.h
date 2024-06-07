#pragma once

#include "Qbit/Core/KeyCodes.h"
#include "Qbit/Core/MouseCodes.h"

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