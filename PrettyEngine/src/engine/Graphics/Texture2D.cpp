#include "pepch.h"
#include "Texture2D.h"
#include "engine\Core\Context.h"

#include "Platform\OpenGL\GLTexture2D.h"

namespace PrettyEngine {
	Texture2D * Texture2D::Create(uint width, uint height, TextureParameters parameters, TextureLoadOptions loadOptions)
	{
		switch (Context::GetRenderAPI())
		{
		case RenderAPI::OPENGL:		return new GLTexture2D(width, height, parameters, loadOptions);
		case RenderAPI::DIRECT3D:	PE_CORE_ERROR("No DirectX platform at the moment.");
		}
		return nullptr;
	}

	Texture2D* Texture2D::CreateFromFile(const String& filepath, TextureParameters parameters, TextureLoadOptions loadOptions) 
	{
		switch (Context::GetRenderAPI())
		{
		case RenderAPI::OPENGL:		return new GLTexture2D(filepath, filepath, parameters, loadOptions);
		case RenderAPI::DIRECT3D:	PE_CORE_ERROR("No DirectX platform at the moment.");
		}
		return nullptr;
	}
	Texture2D* Texture2D::CreateFromFile(const String& filepath, TextureLoadOptions loadOptions) 
	{
		switch (Context::GetRenderAPI())
		{
		case RenderAPI::OPENGL:		return new GLTexture2D(filepath, filepath, TextureParameters(), loadOptions);
		case RenderAPI::DIRECT3D:	PE_CORE_ERROR("No DirectX platform at the moment.");
		}
		return nullptr;
	}
	Texture2D* Texture2D::CreateFromFile(const String& name, const String& filepath, TextureParameters parameters, TextureLoadOptions loadOptions) 
	{
		switch (Context::GetRenderAPI())
		{
		case RenderAPI::OPENGL:		return new GLTexture2D(name, filepath, parameters, loadOptions);
		case RenderAPI::DIRECT3D:	PE_CORE_ERROR("No DirectX platform at the moment.");
		}
		return nullptr;
	}
	Texture2D* Texture2D::CreateFromFile(const String& name, const String& filepath, TextureLoadOptions loadOptions) 
	{
		switch (Context::GetRenderAPI())
		{
		case RenderAPI::OPENGL:		return new GLTexture2D(name, filepath, TextureParameters(), loadOptions);
		case RenderAPI::DIRECT3D:	PE_CORE_ERROR("No DirectX platform at the moment.");
		}
		return nullptr;
	}
}