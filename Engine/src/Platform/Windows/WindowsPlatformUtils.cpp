#include "qbpch.h"
#include "Qbit/Utils/PlatformUtils.h"
#include "Qbit/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Qbit {

	float Time::GetTime()
	{
		return (float)glfwGetTime();
	}
}