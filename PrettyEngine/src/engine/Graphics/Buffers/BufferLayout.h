#pragma once
#include "Types.h"
#include "engine\Core\Core.h"
#include "engine\Core\Context.h"
#include "engine\Maths\maths.h"
#include <vector>

//TODO: Make a way to include only necessary stuff from glad
#include "Platform\OpenGL\GLTypes.h"

namespace PrettyEngine {

	struct BufferElement {

		String name;
		uint type;
		uint size;
		uint offset;
		uint count;
		bool normalized;
	};

	//Remove PE_API. Used for testing only
	class BufferLayout
	{
	public:
		BufferLayout();
		~BufferLayout();

	public:
		template <typename T>
		void Push(const String& name, uint count = 1, bool normalized = false) {
			PE_CORE_ASSERT(false, "Layout: Unknown type!");
		}

		template<>
		void Push<uint>(const String& name, uint count, bool normalized)
		{
			switch (Context::GetRenderAPI())
			{
			case RenderAPI::OPENGL:
				Push(name, GL_UNSIGNED_INT, sizeof(uint), count, normalized);
				break;

			case RenderAPI::DIRECT3D:
				break;
			}
		}

		template<>
		void Push<byte>(const String& name, uint count, bool normalized)
		{
			switch (Context::GetRenderAPI())
			{
			case RenderAPI::OPENGL:
				Push(name, GL_UNSIGNED_BYTE, sizeof(byte), count, normalized);
				break;

			case RenderAPI::DIRECT3D:
				break;
			}
		}

		template<>
		void Push<float>(const String& name, uint count, bool normalized)
		{
			switch (Context::GetRenderAPI())
			{
			case RenderAPI::OPENGL:
				Push(name, GL_FLOAT, sizeof(float), count, normalized);
				break;

			case RenderAPI::DIRECT3D:
				break;
			}
		}

		template<>
		void Push<Vector2>(const String& name, uint count, bool normalized)
		{
			switch (Context::GetRenderAPI())
			{
			case RenderAPI::OPENGL:
				Push(name, GL_FLOAT, sizeof(float), 2, normalized);
				break;

			case RenderAPI::DIRECT3D:
				break;
			}
		}

			template<>
		void Push<Vector3>(const String& name, uint count, bool normalized)
		{
			switch (Context::GetRenderAPI())
			{
			case RenderAPI::OPENGL:
				Push(name, GL_FLOAT, sizeof(float), 3, normalized);
				break;

			case RenderAPI::DIRECT3D:
				break;
			}
		}

				template<>
		void Push<Vector4>(const String& name, uint count, bool normalized)
		{
			switch (Context::GetRenderAPI())
			{
			case RenderAPI::OPENGL:
				Push(name, GL_FLOAT, sizeof(float), 4, normalized);
				break;

			case RenderAPI::DIRECT3D:
				break;
			}
		}

	public:
		inline const std::vector<BufferElement> GetLayout() const { return m_Layout; }
		inline uint GetStride() const { return m_Size; }

	private:
		uint m_Size;
		std::vector<BufferElement> m_Layout;

	private:
		void Push(const String& name, uint type, uint size, uint count, bool normalized);
	};

}