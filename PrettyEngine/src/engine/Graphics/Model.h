#pragma once
#include "engine\Graphics\Mesh.h"

namespace PrettyEngine 
{
	class Renderer3D;

	struct BoundingBox2D {
		Vector2 min;
		Vector2 max;
	};

	class PE_API Model 
	{
	public:
		Model();
		Model(String filePath, BufferUsage usage = BufferUsage::STATIC, bool hasMaterial = true, bool hasAnimations = false);
		Model(String filePath, Material* material, BufferUsage usage = BufferUsage::STATIC, bool hasAnimations = false);
		~Model();

		void SetMaterial(Material* material);
		void Reload();

		//inline int GetMeshCount() const { return m_Meshes.size(); }
		inline const std::vector<Mesh*>& GetMeshes() const { return m_Meshes; }
		inline const int& GetMesheCount() const { return m_Meshes.size(); }

		
		inline const BoundingBox2D& GetBoundingBox() const { return m_BB2D; }
		inline const String& GetFilePath() const { return m_FilePath; }
		inline void SetFilePath(const String& path) { m_FilePath = path; }
		//void Submit(Renderer3D* renderer) const;

	private:
		String m_FilePath;
		std::vector<Mesh*> m_Meshes;
		BoundingBox2D m_BB2D;

		//Matrix4 m_TransformationMatrix;
	};

}