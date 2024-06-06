#include "qbpch.h"
#include "Qbit/Core/Window.h"

#ifdef QB_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Qbit
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef QB_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		QB_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}