#pragma once


#include "engine\Core\Core.h"
#include "Shader.h"

#include <vector>

namespace PrettyEngine {

	class PE_API ShaderManager
	{
	private:
		static std::vector<Shader*> s_Shaders;
	public:
		static void Add(Shader* shader);
		static Shader* Get(const String& name);
		static void Clean();

		static void Reload(const String& name);
		static void Reload(const Shader* shader);
	private:
		ShaderManager() { }
	};
}