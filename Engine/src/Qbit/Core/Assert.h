#pragma once

#include "Qbit/Core/Base.h"
#include "Qbit/Core/Log.h"
#include <filesystem>


#ifdef QB_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
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