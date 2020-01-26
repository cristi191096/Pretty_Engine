#include "pepch.h"
#include "ShaderManager.h"

namespace PrettyEngine {

	std::vector<Shader*>  ShaderManager::s_Shaders = {};

	void ShaderManager::Add(Shader* shader)
	{
		s_Shaders.push_back(shader);
	}

	Shader * ShaderManager::Get(const String& name)
	{
		for (Shader* shader : s_Shaders) 
		{
			if (shader->GetName() == name)
				return shader;
		}
		return nullptr;
	}
}