#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog\fmt\ostr.h"

namespace PrettyEngine {

	class PE_API Log
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

//Core log macros
#define PE_CORE_FATAL(...) ::PrettyEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define PE_CORE_ERROR(...) ::PrettyEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PE_CORE_WARN(...)  ::PrettyEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PE_CORE_INFO(...)  ::PrettyEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PE_CORE_TRACE(...) ::PrettyEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)


//Client log macros
#define PE_FATAL(...) ::PrettyEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define PE_ERROR(...) ::PrettyEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define PE_WARN(...)  ::PrettyEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PE_INFO(...)  ::PrettyEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define PE_TRACE(...) ::PrettyEngine::Log::GetClientLogger()->trace(__VA_ARGS__)

