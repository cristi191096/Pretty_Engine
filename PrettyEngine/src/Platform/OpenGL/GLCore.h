#pragma once

#include <glad\glad.h>
namespace PrettyEngine {
	extern GLenum GLCheckError();
	extern bool GLLogCall(const char* function, const char* file, int line);
}

#ifdef PE_DEBUG

	#define GLCall(x) PrettyEngine::GLCheckError();\
				x; \
				if (!PrettyEngine::GLLogCall(#x, __FILE__, __LINE__)) __debugbreak();
	#else
		#define GLCall(x) x

#endif // PE_DEBUG
