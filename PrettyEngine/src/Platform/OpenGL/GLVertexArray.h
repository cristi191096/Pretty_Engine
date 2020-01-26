#pragma once
#include "engine\Graphics\Buffers\VertexArray.h"

namespace PrettyEngine {

	class GLVertexArray : public VertexArray
	{
	public:
		GLVertexArray();
		~GLVertexArray();

		
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void PushBuffer(VertexBuffer* buffer) override;
		inline VertexBuffer* GetBuffer(uint index = 0) override { return m_Buffers[index]; }

		virtual void Draw(uint count) const override;

	private:
		uint m_ID;
		std::vector<VertexBuffer*> m_Buffers;
	};

	
}
