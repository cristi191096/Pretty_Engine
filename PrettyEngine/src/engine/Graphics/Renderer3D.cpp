#include "pepch.h"
#include "Renderer3D.h"
#include "engine\Graphics\Cameras\Camera.h"

#include "engine\Graphics\Model.h"

#define MAX_LIGHTS 10

namespace PrettyEngine {
	Renderer3D::Renderer3D(Camera * camera)
		: m_Camera(camera)
	{
		Init();
	}
	Renderer3D::~Renderer3D()
	{
		delete m_Camera;
	}


	void Renderer3D::Submit(Renderable3D renderable)
	{
		SetProjection(renderable.shader);
		m_Renderables.push_back(renderable);
	}

	void Renderer3D::Submit(Mesh * mesh, Matrix4* transform)
	{

		Renderable3D toRender;
		toRender.mesh = mesh;
		toRender.shader = mesh->GetMaterial()->GetShader();
		toRender.transform = transform;

		Submit(toRender);
	}

	void Renderer3D::Submit(Light * light)
	{
		m_Lights.push_back(light);
	}

	void Renderer3D::Flush()
	{
		for (uint i = 0; i < m_Renderables.size(); i++)
		{
			Renderable3D& renderable = m_Renderables[i];
			Material* material = renderable.mesh->GetMaterial();
			material->Bind();
			if (renderable.shader->GetType() == Shader::Type::BLINPHONG)	// The material reacts to light. Bind light uniforms
			{
				// TODO: Check that the number of lights matches with the number in the shader
				renderable.shader->SetUniform3f("u_CameraPosition", m_Camera->GetPosition());

				for (uint j = 0; j < m_Lights.size(); j++)
					m_Lights[j]->SetUniforms(renderable.shader);
				
			}
			//Bind matrices
			renderable.shader->SetUniformMat4("u_ViewMatrix", m_Camera->GetViewMatrix());
			renderable.shader->SetUniformMat4("u_ModelMatrix", *renderable.transform);
			//PE_CORE_TRACE("ModelMatrix: {0}", renderable.transform->ToString());
			renderable.mesh->Render();
			material->Unbind();
		}

	

	}

	// Allow the change of the view from where the scene is rendered. Might need to reset the projection matrix when this method is called
	void Renderer3D::SetCamera(Camera * camera)
	{
		m_Camera = camera;

	}

	void Renderer3D::Init()			// I was thinking to set the camera and the projection matrix here, but i don't know the shader yet
	{
	}

	void Renderer3D::SetProjection(Shader * shader)
	{
		shader->Bind();
		shader->SetUniformMat4("u_ProjectionMatrix", m_Camera->GetProjectionMatrix());
		
		shader->Unbind();
	}


}