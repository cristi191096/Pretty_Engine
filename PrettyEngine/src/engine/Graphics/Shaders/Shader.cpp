#include "pepch.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "engine\Core\Context.h"
#include "Platform\OpenGL\GLShader.h"
#include "Utilities\Files.h"

namespace PrettyEngine {

	Shader* Shader::CreateFromFile(const String & name, const String & filePath)
	{
		String source = FileSystem::ReadTextFile(filePath);
		
		switch (Context::GetRenderAPI())
		{
		case RenderAPI::OPENGL:
			//This change was made due to newShader initialization. Could not initialize it if it is case specific.
			//GLShader* newShader = new GLShader(name, source);
			ShaderManager::Add(new GLShader(name, source));
			ShaderManager::Get(name)->SetFilePath(filePath);
			return ShaderManager::Get(name);

		case RenderAPI::DIRECT3D:
			PE_CORE_ERROR("No DirectX shader at the moment.");
			break;
		
		}
		return nullptr;
	}

	Shader* Shader::CreateFromSource(const String & name, const String & source)
	{
		switch (Context::GetRenderAPI())
		{
		case RenderAPI::OPENGL:
			//GLShader* newShader = new GLShader(name, source);
			ShaderManager::Add(new GLShader(name, source));
			return ShaderManager::Get(name);

		case RenderAPI::DIRECT3D:
			PE_CORE_ERROR("No DirectX shader at the moment.");
			break;
		
		}
		return nullptr;
	}

}