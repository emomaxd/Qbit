#pragma once

#include <filesystem>
#include <memory>
#include "log.h"


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



#ifdef QB_ENABLE_ASSERTS

#define QB_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { QB##type##ERROR(msg, __VA_ARGS__); QB_DEBUGBREAK(); } }
#define QB_INTERNAL_ASSERT_WITH_MSG(type, check, ...) QB_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define QB_INTERNAL_ASSERT_NO_MSG(type, check) QB_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", QB_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define QB_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define QB_INTERNAL_ASSERT_GET_MACRO(...) QB_EXPAND_MACRO( QB_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, QB_INTERNAL_ASSERT_WITH_MSG, QB_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define QB_ASSERT(...) QB_EXPAND_MACRO( QB_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define QB_CORE_ASSERT(...) QB_EXPAND_MACRO( QB_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )

#else
#define QB_ASSERT(...)
#define QB_CORE_ASSERT(...)

#endif