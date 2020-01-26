#pragma once

#include "BufferLayout.h"


namespace PrettyEngine {

	enum class BufferUsage {
		STATIC, DYNAMIC, STREAM
	};

	typedef unsigned int uint;

	//Remove PE_API. Used for testing only 
	class PE_API VertexBuffer {

	public:
		static VertexBuffer* Create(BufferUsage usage = BufferUsage::STATIC);


	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(uint size, const void* data) = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		virtual void Resize(uint size) = 0;
		virtual void ReleasePointer() = 0;

		template <typename T>
		T* GetPointer() {
			return (T*)GetPointerInternal();
		}

	protected:
		virtual void* GetPointerInternal() = 0;
	};
}