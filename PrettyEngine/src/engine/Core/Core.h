#pragma once

#pragma region Platform specific definitions
#ifdef PE_PLATFORM_WINDOWS
#if PE_DYNAMIC_LINKING
	#ifdef PE_BUILD_DLL
		#define PE_API __declspec(dllexport)
	#else
		#define PE_API __declspec(dllimport)
	#endif // PE_BUILD_DLL
#else
	#define PE_API
#endif

#else
	#error PrettyEngine only supports Windows!

#endif // PE_PLATFORM_WINDOWS
#pragma endregion 

#pragma region Debug configuration

#ifdef PE_DEBUG
	#define PE_ENABLE_ASSERTS
//OpenGL
	
#endif

#ifdef PE_ENABLE_ASSERTS
	#define PE_ASSERT(x, ...) { if(!(x)) { PE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PE_CORE_ASSERT(x, ...) { if(!(x)) { PE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PE_ASSERT(x, ...)
	#define PE_CORE_ASSERT(x, ...)
#endif // PE_ENABLE_ASSERTS

#pragma endregion


#define BIT(x) (1 << x)		// Make BitMask
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)		// Creates a function callback to x. placeholders::_1 means expect 1 argument. 
																		// Use std::bind because I want the callback (void*) to belong to an object, so it's not static. 