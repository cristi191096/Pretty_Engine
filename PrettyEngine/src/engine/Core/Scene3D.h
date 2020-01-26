#pragma once
#include "Scene.h"
#include "engine\ECS\Entity.h"
#include "engine\Graphics\Cameras\StaticCamera.h"
#include "engine\Graphics\Renderer3D.h"

namespace PrettyEngine {

	class Scene3D : public Scene
	{
	public:
		Scene3D(Camera* camera);
		~Scene3D();

		virtual void Submit() override;
		virtual void RenderScene() override;
		virtual void OnEvent(Event & ev) override;

		virtual Entity* GetEntityByTag(const String& tag) override;

			
		virtual void AddInternal(void* renderable) override {
			if (static_cast<Entity*>(renderable)) 
			{
				m_Entities.push_back((Entity*)renderable);
				return;
			}
			if (static_cast<StaticCamera*>(renderable)) 
			{
				m_Cameras.push_back((StaticCamera*)renderable); 
				return;
			}
		}

		virtual void RemoveInternal(void* renderable) override
		{
			if (static_cast<Entity*>(renderable))
			{
				auto it = std::find(m_Entities.begin(), m_Entities.end(), renderable);
				if (it != m_Entities.end())
				{
					m_Entities.erase(it);
				}
			}
		}

		virtual const std::vector<Entity*>& GetEntitiesInternal() const override { return m_Entities; }

	private:
		Renderer3D* m_Renderer;
		std::vector<Entity*> m_Entities;
		std::vector<StaticCamera*> m_Cameras;
	};

	
}