#pragma once

//#include "Hazel/Core/PlatformDetection.h"

#include <memory>



#ifdef QB_DEBUG
#if defined(QB_PLATFORM_WINDOWS)
#define QB_DEBUGBREAK() __debugbreak()
#elif defined(HZ_PLATFORM_LINUX)
#include <signal.h>
#define QB_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define QB_ENABLE_ASSERTS
#else
#define QB_DEBUGBREAK()
#endif



#define QB_EXPAND_MACRO(x) x
#define QB_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define QB_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Qbit {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#include "Qbit/Core/Log.h"
#include "Qbit/Core/Assert.h"