#pragma once
#include "engine\Maths\maths.h"
#include "engine\Graphics\Mesh.h"
#include "engine\Graphics\Light.h"

namespace PrettyEngine {


	struct Renderable3D {
		//mesh
		Mesh* mesh;
		//shader
		Shader* shader;
		//transform
		Matrix4* transform;
		
	};

	class Model;
	class Camera;

	class Renderer3D
	{
	public:
		Renderer3D(Camera* camera);
		~Renderer3D();

	
		void Submit(Renderable3D renderable);
		void Submit(Mesh* mesh, Matrix4* transform);
		void Submit(Light* light);
		void Flush();

		void SetCamera(Camera* camera);
		inline void Clear() { m_Renderables.clear(); m_Lights.clear(); }
		
	private:
		std::vector<Renderable3D> m_Renderables;
		std::vector<Light*> m_Lights;

		Camera* m_Camera;

	private:
		void Init();
		void SetProjection(Shader* shader);


	};
}