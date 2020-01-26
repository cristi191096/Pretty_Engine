#pragma once

#include "engine\Graphics\Buffers\IndexBuffer.h"

namespace PrettyEngine {

	class GLIndexBuffer : public IndexBuffer
	{
	public:
		GLIndexBuffer(uint* data, uint count);
		GLIndexBuffer(std::vector<uint> data);
		~GLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;
		
		uint GetCount() const override;

	private:
		uint m_ID;
		uint m_Count;
	};

}