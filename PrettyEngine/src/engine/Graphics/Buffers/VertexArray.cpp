#include "pepch.h"
#include "VertexArray.h"

#include "Platform\OpenGL\GLVertexArray.h"

#include "engine\Core\Context.h"


namespace PrettyEngine {

	VertexArray* VertexArray::Create()
	{
		switch (Context::GetRenderAPI())
		{
		case RenderAPI::OPENGL:				return new GLVertexArray();
		case RenderAPI::DIRECT3D:
			PE_CORE_ERROR("No DirectX platform at the moment.");
			break;
		}
		return nullptr;
	}
}