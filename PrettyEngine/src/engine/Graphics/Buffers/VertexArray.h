#pragma once

#include "VertexBuffer.h"

namespace PrettyEngine {

	typedef unsigned int uint;

	//Remove PE_API. Used for testing only
	class PE_API VertexArray
	{
	public:
		static VertexArray* Create();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void PushBuffer(VertexBuffer* buffer) = 0;
		virtual VertexBuffer* GetBuffer(uint index = 0) = 0;

		virtual void Draw(uint count) const = 0;

	private:
		uint m_ID;
		std::vector<VertexBuffer*> m_Buffers;
	};

}