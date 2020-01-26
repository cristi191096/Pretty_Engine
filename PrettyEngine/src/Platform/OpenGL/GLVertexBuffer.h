#pragma once
#include "engine\Graphics\Buffers\VertexBuffer.h"

namespace PrettyEngine {

	class GLVertexBuffer : public VertexBuffer
	{
	public:
		GLVertexBuffer(BufferUsage usage);
		~GLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		void SetData(uint size, const void* data) override;
		void SetLayout(const BufferLayout& layout) override;

		void Resize(uint size) override;
		void ReleasePointer() override;

		void* GetPointerInternal() override;

	private:
		uint m_ID;
		uint m_Size;
		BufferUsage m_Usage;
		BufferLayout m_Layout;

	};

}