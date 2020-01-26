#include "pepch.h"
#include "BufferLayout.h"

namespace PrettyEngine {

	BufferLayout::BufferLayout()
		: m_Size(0)
	{
	}

	BufferLayout::~BufferLayout()
	{
	}

	void BufferLayout::Push(const String & name, uint type, uint size, uint count, bool normalized)
	{
		m_Layout.push_back({ name, type, size, m_Size, count, normalized });
		m_Size += size * count;
	}
}