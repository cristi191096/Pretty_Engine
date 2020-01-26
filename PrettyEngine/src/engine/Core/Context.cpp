#include "pepch.h"
#include "Context.h"
#include "Platform\OpenGL\GLContext.h"



namespace PrettyEngine {

	Context* Context::s_Context = nullptr;
	RenderAPI Context::s_RenderAPI = RenderAPI::NONE;

	void Context::Create(Window::WindowData& properties)
	{
		switch (GetRenderAPI())
		{
			case RenderAPI::OPENGL:		s_Context = new GLContext(properties); break;
			case RenderAPI::DIRECT3D:	PE_CORE_ERROR("No DirectX platform at the moment.");; break;
		}
	}
	
}