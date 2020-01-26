#include "pepch.h"
#include "Mesh.h"

namespace PrettyEngine {



	//Mesh::Mesh(VertexArray * va, IndexBuffer * ib, Material * mat, BufferUsage usage)
	//	: m_VAO(va), m_IBO(ib), m_Material(mat)
	//{
	//}

	Mesh::Mesh(std::vector<Vertex> verts, IndexBuffer * ib, BufferUsage usage)
		: m_IBO(ib)
	{
		m_VAO = VertexArray::Create();
		m_VBO = VertexBuffer::Create(usage);

		m_VBO->Bind();
		m_VAO->Bind();
		if (m_Material != nullptr)
			m_VBO->SetLayout(m_Material->GetShader()->GetLayout()); // get the layout
		m_VBO->SetData(verts.size() * sizeof(Vertex), verts.data());
		m_VAO->PushBuffer(m_VBO);

		m_VAO->Unbind();
	}

	Mesh::Mesh(std::vector<Vertex> verts, IndexBuffer * ib, Material * mat, BufferUsage usage)
		: m_IBO(ib), m_Material(mat)
	{
		m_VAO = VertexArray::Create();
		m_VBO = VertexBuffer::Create(usage);
		m_VBO->Bind();
		m_VAO->Bind();
		m_VBO->SetLayout(m_Material->GetShader()->GetLayout()); // get the layout
		m_VBO->SetData(verts.size() * sizeof(Vertex), verts.data());
		m_VAO->PushBuffer(m_VBO);
		m_VAO->Unbind();
	}

	Mesh::~Mesh()
	{
		delete m_VAO;
		delete m_IBO;
		delete m_VBO;
		delete m_Material;
	}

	void Mesh::SetMaterial(Material * material)
	{
		m_Material = material;
		m_VBO->Bind();
		m_VAO->Bind();
		m_VBO->SetLayout(m_Material->GetShader()->GetLayout());
		m_VAO->Unbind();
	}

	void Mesh::Render()
	{
		//m_Material->Bind();
		m_VAO->Bind();
		m_IBO->Bind();
		m_VAO->Draw(m_IBO->GetCount());
		m_IBO->Unbind();
		m_VAO->Unbind();
		//m_Material->Unbind();
	}

}
