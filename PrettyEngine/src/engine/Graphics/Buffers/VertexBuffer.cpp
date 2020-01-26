#include "pepch.h"

#include "engine\Core\Context.h"
#include "VertexBuffer.h"

#include "Platform\OpenGL\GLVertexBuffer.h"

namespace PrettyEngine {

	VertexBuffer* VertexBuffer::Create(BufferUsage usage)
	{
		switch (Context::GetRenderAPI())
		{
		case RenderAPI::OPENGL:
			return new GLVertexBuffer(usage);

		case RenderAPI::DIRECT3D:
			PE_CORE_ERROR("No DirectX platform at the moment.");
			break;
		}

		return nullptr;
	}
}
