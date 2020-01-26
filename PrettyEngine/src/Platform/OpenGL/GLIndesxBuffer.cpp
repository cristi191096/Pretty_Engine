#include "pepch.h"
#include "GLIndexBuffer.h"

#include "GLCore.h"

namespace PrettyEngine {

	GLIndexBuffer::GLIndexBuffer(uint* data, uint count)
		: m_Count(count)
	{
		GLCall(glGenBuffers(1, &m_ID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW));
	}

	GLIndexBuffer::GLIndexBuffer(std::vector<uint> data)
	{
		m_Count = data.size();
		GLCall(glGenBuffers(1, &m_ID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(uint), data.data(), GL_STATIC_DRAW));
	}

	GLIndexBuffer::~GLIndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_ID));
	}

	void GLIndexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	}

	void GLIndexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	uint GLIndexBuffer::GetCount() const
	{
		return m_Count;
	}
}