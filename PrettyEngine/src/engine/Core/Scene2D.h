#pragma once
#include "Scene.h"
#include "engine\Graphics\Renderer2D.h"
#include "engine\Graphics\Renderable2D.h"

namespace PrettyEngine {

	// TODO: Add ECS to the 2D system.

	class Scene2D : public Scene 
	{
	public:
		Scene2D(Camera* camera);
		~Scene2D();


		virtual void Submit() override;
		virtual void RenderScene() override;
		virtual void OnEvent(Event & ev) override;

		virtual void BeginScene() const override { m_Renderer->Begin(); }
		virtual void EndScene() const	override { m_Renderer->End(); }

		virtual void DrawLine(const Vector2& start, const Vector2& end, const Vector4& color = Vector4(1.0f), float thickness = 0.02f) override;
		virtual void DrawRect(const Vector2& position, const Vector2& size, const Vector4& color = Vector4(1.0f), float thickness = 0.02f) override;
		
		virtual void AddInternal(void* renderable) override
		{
			if (static_cast<Renderable2D*>(renderable))
			{
				m_Renderables.push_back((Renderable2D*)renderable);
			}
		}

		virtual void RemoveInternal(void* renderable) override
		{
			if (static_cast<Renderable2D*>(renderable))
			{
				auto it = std::find(m_Renderables.begin(), m_Renderables.end(), renderable);
				if (it != m_Renderables.end())
				{
					m_Renderables.erase(it);
				}
			}
		}

		virtual const std::vector<Renderable2D*>& GetRenderablesInternal() const override { return m_Renderables; }

		
	private:
		Renderer2D* m_Renderer;
		std::vector<Renderable2D*> m_Renderables;

	};
}