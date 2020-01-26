#include "pepch.h"
#include "Scene2D.h"
#include "engine\Graphics\Renderer.h" 

namespace PrettyEngine {

	Scene2D::Scene2D(Camera* camera) : Scene(camera)
	{
		m_Renderer = new Renderer2D(camera);
	}
	Scene2D::~Scene2D()
	{
	}
	void Scene2D::Submit()
	{
		//m_Renderer->Begin();
		//m_Renderer->DrawLine(Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), Vector4(1.0f, 0.0f, 0.0f, 0.5f), 0.1f);
		//m_Renderer->DrawRect(Vector2(0.0f, 0.0f), Vector2(3.0f, 3.0f));
		for (Renderable2D* renderable : m_Renderables)
			renderable->Submit(m_Renderer);
		//m_Renderer->End();
	}
	void Scene2D::RenderScene()
	{
		//Renderer::Clear(RendererBufferType::COLOR | RendererBufferType::DEPTH);
		m_Camera->Update();

			m_Renderer->Flush();
	}
	void Scene2D::OnEvent(Event & ev)
	{
	}
	void Scene2D::DrawLine(const Vector2 & start, const Vector2 & end, const Vector4 & color, float thickness)
	{
		m_Renderer->DrawLine(start, end, color, thickness);
	}
	void Scene2D::DrawRect(const Vector2 & position, const Vector2 & size, const Vector4 & color, float thickness)
	{
		uint col = (uint)(color.w * 255.0f) << 24 | (uint)(color.z * 255.0f) << 16 | (uint)(color.y * 255.0f) << 8 | (uint)(color.x * 255.0f);
		m_Renderer->DrawRect(position, size, col, thickness);
	}
}