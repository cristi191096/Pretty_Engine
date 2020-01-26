#include "pepch.h"
#include "IndexBuffer.h"

#include "Platform\OpenGL\GLIndexBuffer.h"

#include "engine\Core\Context.h"

namespace PrettyEngine {

	IndexBuffer * IndexBuffer::Create(uint* data, uint count)
	{
		switch (Context::GetRenderAPI())
		{
		case RenderAPI::OPENGL:		return new GLIndexBuffer(data, count);
		case RenderAPI::DIRECT3D:
			PE_CORE_ERROR("No DirectX platform at the moment.");
			break;
		
		}

		return nullptr;
	}
	IndexBuffer * IndexBuffer::Create(std::vector<uint> data)
	{
		switch (Context::GetRenderAPI())
		{
		case RenderAPI::OPENGL:		return new GLIndexBuffer(data);
		case RenderAPI::DIRECT3D:
			PE_CORE_ERROR("No DirectX platform at the moment.");
			break;
		
		}

		return nullptr;
	}
}