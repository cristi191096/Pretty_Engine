#include "pepch.h"
#include "Renderer.h"
#include "engine\Core\Context.h"
#include "Platform\OpenGL\GLRenderer.h"

namespace PrettyEngine {

	Renderer* Renderer::s_Instance = nullptr;

	void Renderer::Init()
	{
		switch (Context::GetRenderAPI())
		{
		case RenderAPI::OPENGL:
			s_Instance = new GLRenderer();
			break;
		case RenderAPI::DIRECT3D:
			PE_CORE_ERROR("No DirectX platform at the moment.");
			break;
		default:
			break;
		}
		s_Instance->InitInternal();
	}
}