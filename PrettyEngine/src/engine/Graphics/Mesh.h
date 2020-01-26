#pragma once
#include "engine\Core\Core.h"
#include "engine\Graphics\Material.h"
#include "engine\Graphics\Buffers\VertexBuffer.h"
#include "engine\Graphics\Buffers\IndexBuffer.h"
#include "engine\Graphics\Buffers\VertexArray.h"

namespace PrettyEngine {

	struct PE_API Vertex
	{
		Vector3 position;
		Vector3 normal;
		Vector2 uv;
		Vector3 bitangent;
		Vector3 tangent;
	};



	class PE_API Mesh {

	public:
		//Mesh(VertexArray* va, IndexBuffer* ib, Material* mat, BufferUsage usage = BufferUsage::STATIC);
		Mesh(std::vector<Vertex> verts, IndexBuffer* ib, BufferUsage usage = BufferUsage::STATIC);
		Mesh(std::vector<Vertex> verts, IndexBuffer* ib, Material* mat, BufferUsage usage = BufferUsage::STATIC);
		~Mesh();

		void SetMaterial(Material* material);
		inline Material* GetMaterial() const { return m_Material; }

		void Render();

	private:
		Material* m_Material = nullptr;
		IndexBuffer* m_IBO;
		VertexArray* m_VAO;
		VertexBuffer* m_VBO;
	
	};
}