#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <memory>

namespace Qbit {


	class Log
	{
	public:
		static void Init();
		

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// CORE
#define QB_CORE_TRACE(...)    ::Qbit::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define QB_CORE_INFO(...)     ::Qbit::Log::GetCoreLogger()->info(__VA_ARGS__)
#define QB_CORE_WARN(...)     ::Qbit::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define QB_CORE_ERROR(...)    ::Qbit::Log::GetCoreLogger()->error(__VA_ARGS__)
#define QB_CORE_CRITICAL(...)    ::Qbit::Log::GetCoreLogger()->critical(__VA_ARGS__)


// CLIENT
#define QB_TRACE(...)         ::Qbit::Log::GetClientLogger()->trace(__VA_ARGS__)
#define QB_INFO(...)          ::Qbit::Log::GetClientLogger()->info(__VA_ARGS__)
#define QB_WARN(...)          ::Qbit::Log::GetClientLogger()->warn(__VA_ARGS__)
#define QB_ERROR(...)         ::Qbit::Log::GetClientLogger()->error(__VA_ARGS__)
#define QB_CRITICAL(...)         ::Qbit::Log::GetClientLogger()->critical(__VA_ARGS__)
