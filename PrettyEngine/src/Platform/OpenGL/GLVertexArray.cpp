#include "pepch.h"
#include "GLVertexArray.h"
#include "GLCore.h"

namespace PrettyEngine {

	GLVertexArray::GLVertexArray()
	{
		GLCall(glGenVertexArrays(1, &m_ID));
	}

	GLVertexArray::~GLVertexArray()
	{
	}

	void GLVertexArray::Bind() const
	{
		if (m_Buffers.size() != 0)
			m_Buffers.front()->Bind();
		GLCall(glBindVertexArray(m_ID));
	}

	void GLVertexArray::Unbind() const
	{
		if (m_Buffers.size() != 0)
			m_Buffers.front()->Unbind();
		GLCall(glBindVertexArray(0));
	}

	void GLVertexArray::PushBuffer(VertexBuffer * buffer)
	{
		m_Buffers.push_back(buffer);
	}

	void GLVertexArray::Draw(uint count) const
	{
		GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));
	}

}