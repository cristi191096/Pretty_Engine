#include "pepch.h"
#include "GLCore.h"
#include "GLVertexBuffer.h"

namespace PrettyEngine {

	static uint BufferUsageToGL(BufferUsage usage) 
	{
		switch (usage) 
		{
		case BufferUsage::STATIC:		return GL_STATIC_DRAW;
		case BufferUsage::DYNAMIC:		return GL_DYNAMIC_DRAW;
		}

	}

	static BufferUsage GLToBufferUsage(uint usage) 
	{
		switch (usage) 
		{
		case GL_STATIC_DRAW:		return BufferUsage::STATIC;
		case GL_DYNAMIC_DRAW:		return BufferUsage::DYNAMIC;
		}

	}

	GLVertexBuffer::GLVertexBuffer(BufferUsage usage)
		: m_Usage(usage)
	{
		GLCall(glGenBuffers(1, &m_ID));
		
	}

	GLVertexBuffer::~GLVertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_ID));
	}

	void GLVertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
		//TODO: Set layout here
		//-------Maybe is not such a good idea.
	}

	void GLVertexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void GLVertexBuffer::SetData(uint size, const void* data)
	{
		m_Size = size;
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, BufferUsageToGL(m_Usage)));
	}

	void GLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_Layout = layout;
		const std::vector<BufferElement>& elements = layout.GetLayout();

		Bind();
		for (uint i = 0; i < elements.size(); i++) 
		{
			const BufferElement& element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)element.offset));
		}
	}

	void GLVertexBuffer::Resize(uint size)
	{
		m_Size = size;

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, NULL, BufferUsageToGL(m_Usage)));
	}

	void GLVertexBuffer::ReleasePointer()
	{
		GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
	}

	void* GLVertexBuffer::GetPointerInternal()
	{
		GLCall(void* result = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		return result;
	}

}
