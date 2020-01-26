#include "pepch.h"
#include "Scene3D.h"
#include "engine\Graphics\Renderer.h" 
#include "engine\ECS\Components\TransformComponent.h"
#include "engine\ECS\Components\ModelComponent.h"
#include "engine\ECS\Components\LightComponent.h"



namespace PrettyEngine {


	Scene3D::Scene3D(Camera* camera) : Scene(camera)
	{
		m_Renderer = new Renderer3D(camera);
	}
	Scene3D::~Scene3D()
	{
		delete m_Renderer;
		for (Entity* entity : m_Entities)
			delete entity;

		m_Entities.clear();
	}
	void Scene3D::Submit()
	{
		m_Renderer->Clear();
		
		for (Entity* entity : m_Entities) {
			Transform* tr = entity->GetComponent<Transform>();		// I know they all have a transform
	
			//Build the Renderable3D and submit to the renderer
			
				ModelComponent* model = entity->GetComponent<ModelComponent>();
				if (model != nullptr) {
					for (Mesh* mesh : model->model->GetMeshes()) {
						m_Renderer->Submit(mesh, tr->ModelMatrix());
					}
				}
		
				LightComponent* lightComp = entity->GetComponent<LightComponent>();
				if (lightComp != nullptr)
					m_Renderer->Submit(lightComp->light);

			

		}
	}
	void Scene3D::RenderScene()
	{
		/*Renderer::ClearColour(Vector4(0.12f, 0.1f, 0.1f, 1.f));
		Renderer::Clear(RendererBufferType::COLOR | RendererBufferType::DEPTH);*/
		//Renderer::SetDepthTesting(false);
		m_Camera->Update();


		for (Entity* entity : m_Entities) {
			Transform* tr = entity->GetComponent<Transform>();
			tr->Update();


		}
		m_Renderer->Flush();
	}
	void Scene3D::OnEvent(Event & ev)
	{
		m_Camera->OnEvent(ev);
	}
	Entity* Scene3D::GetEntityByTag(const String & tag)
	{
		for (Entity* entity : m_Entities) 
		{
			if (entity->tag == tag)
				return entity;
		}
		PE_ERROR("Entity not found! You were looking for tag: {0}", tag);
	}
}