#include "pepch.h"
#include "Model.h"
#include "Utilities\AssetImporter.h"
#include "engine\Graphics\Renderer3D.h"

namespace PrettyEngine {

	Model::Model()
	{
		
	}

	Model::Model(String filePath, BufferUsage usage, bool hasMaterial, bool hasAnimations)
		: m_FilePath(filePath)
	{
		std::vector<MeshData> data = MeshImporter::Get()->Load(filePath, hasMaterial, hasAnimations);
		BB2D temp = data[0].boundingBoxData;

		for (int i = 0; i < data.size(); i++) {
			Mesh* mesh = new Mesh(data[i].vertices, IndexBuffer::Create(data[i].indices ),new Material(data[i].materialMaps), usage);
			if (temp.min > data[i].boundingBoxData.min)
				temp.min = data[i].boundingBoxData.min;  
			if (temp.max < data[i].boundingBoxData.max)
				temp.max = data[i].boundingBoxData.max;

			m_Meshes.push_back(mesh);
		}

		m_BB2D.min = temp.min;
		m_BB2D.max = temp.max;
	}

	Model::Model(String filePath, Material * material, BufferUsage usage,  bool hasAnimations)
		: m_FilePath(filePath)
	{
		std::vector<MeshData> data = MeshImporter::Get()->Load(filePath, true, hasAnimations);
		BB2D temp = data[0].boundingBoxData;

		for (int i = 0; i < data.size(); i++) {

			Mesh* mesh = new Mesh(data[i].vertices, IndexBuffer::Create(data[i].indices), new Material(*material), usage);
			
			if (temp.min > data[i].boundingBoxData.min)
				temp.min = data[i].boundingBoxData.min;
			if (temp.max < data[i].boundingBoxData.max)
				temp.max = data[i].boundingBoxData.max;

			mesh->GetMaterial()->SetTextures(data[i].materialMaps);
			m_Meshes.push_back(mesh);
		}

		m_BB2D.min = temp.min;
		m_BB2D.max = temp.max;
	}

	Model::~Model()
	{
		for (Mesh* mesh : m_Meshes)
			delete mesh;

		m_Meshes.clear();
	}

	void Model::SetMaterial(Material * material)
	{
		for (Mesh* mesh : m_Meshes)
			mesh->SetMaterial(material);
		
	}

	void Model::Reload()
	{
		for (Mesh* mesh : m_Meshes)
			delete mesh;

		m_Meshes.clear();

		std::vector<MeshData> data = MeshImporter::Get()->Load(m_FilePath, true, false);
		BB2D temp = data[0].boundingBoxData;

		for (int i = 0; i < data.size(); i++) {
			Mesh* mesh = new Mesh(data[i].vertices, IndexBuffer::Create(data[i].indices ),new Material(data[i].materialMaps), BufferUsage::STATIC);
			if (temp.min > data[i].boundingBoxData.min)
				temp.min = data[i].boundingBoxData.min;  
			if (temp.max < data[i].boundingBoxData.max)
				temp.max = data[i].boundingBoxData.max;

			m_Meshes.push_back(mesh);
		}

		m_BB2D.min = temp.min;
		m_BB2D.max = temp.max;
	}

	// Potentially useless... Actually not... Well it is!
	//void Model::Submit(Renderer3D * renderer) const
	//{
	//	//Push ModelMatrix into Renderer TransformationStack
	//	//Create a Renderable3D
	//	//Submit Renderable3D or SubmitMesh method -> renderer
	//	//Pop ModelMatrix into Renderer TransformationStack
	//
	//	//renderer->Push(m_TransformationMatrix);
	//
	//	for (Mesh* mesh : m_Meshes)
	//		renderer->Submit(mesh, m_TransformationMatrix);
	//
	//	//renderer->Pop();
	//}

}