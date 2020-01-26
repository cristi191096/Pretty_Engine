#include "pepch.h"

#include "Platform\OpenGL\GLCore.h"



namespace PrettyEngine {

	GLenum GLCheckError()
	{
		return glGetError();
	}

	bool GLLogCall(const char* function, const char* file, int line)
	{
		GLenum error = GLCheckError();
		if (error != GL_NO_ERROR)
		{
			PE_CORE_ERROR("[OpenGL Error] ({0}): {1} {2}: {3}",  error, function, file, line);
			return false;
		}
		return true;
	}
}