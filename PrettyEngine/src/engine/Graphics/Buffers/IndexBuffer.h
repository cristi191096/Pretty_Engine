#pragma once
#include "Types.h"

namespace PrettyEngine {

	//Remove PE_API. Used for testing only
	class PE_API IndexBuffer {

		public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint GetCount() const = 0;
	public:
		//static IndexBuffer* Create(uint16* data, uint count);
		static IndexBuffer* Create(uint* data, uint count);
		static IndexBuffer* Create(std::vector<uint> data);
	};

}