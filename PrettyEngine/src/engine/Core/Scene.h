#pragma once
#include "engine\Core\Core.h"
#include "engine\Graphics\Cameras\Camera.h"

namespace PrettyEngine {
	/*
	Abstract interface for a scene instance. Children: Scene2D, Scene3D
	It keeps account of:
	- Renderables
	- Lights
	- Cameras
	- Renderer
	*/
	class Entity;
	class Renderable2D;

	class PE_API Scene {

	public:
		Scene(Camera* camera);
		virtual ~Scene();

		inline void SetCamera(Camera* camera) { m_Camera = camera; }
		inline Camera* GetCamera() const { return m_Camera; }

		virtual void Submit() = 0;
		virtual void RenderScene() = 0;
		virtual void OnEvent(Event & ev) = 0;

		virtual void BeginScene() const {}
		virtual void EndScene() const	{}

		virtual void DrawLine(const Vector2& start, const Vector2& end, const Vector4& color = Vector4(1.0f), float thickness = 0.02f) {}
		virtual void DrawRect(const Vector2& position, const Vector2& size, const Vector4& color = Vector4(1.0f), float thickness = 0.02f) {}

		inline const String& GetLevelPath() { return m_LevelPath; }
		inline void SetLevelPath(const String& path) { m_LevelPath = path; }

		virtual Entity* GetEntityByTag(const String& tag) { return nullptr; }

		template <typename T>
		void Add(T* renderable) {
			return AddInternal((T*)renderable);
		}

		template <typename T>
		void Remove(T* renderable) {
			return RemoveInternal((T*)renderable);
		}

		template <typename T>
		const std::vector<T*>& GetEntities() const 
		{ 
			PE_CORE_ASSERT(false, "Scene: Unknown type of entities!");
		}

		template <>
		const std::vector<Entity*>& GetEntities<Entity>() const
		{
			return GetEntitiesInternal();
		}
		

		template <>
		const std::vector<Renderable2D*>& GetEntities<Renderable2D>() const
		{
			return GetRenderablesInternal();
		}

	protected: 
		String m_LevelPath = "NULL";
		Camera* m_Camera;

		virtual void AddInternal(void* renderable) = 0;
		virtual void RemoveInternal(void* renderable) = 0;
		virtual const std::vector<Entity*>& GetEntitiesInternal() const { PE_CORE_ASSERT(false, "Scene: Entity getter implemented in Scene3D"); return std::vector<Entity*>(); }
		virtual const std::vector<Renderable2D*>& GetRenderablesInternal() const { PE_CORE_ASSERT(false, "Scene: Renderable getter implemented in Scene2D"); return std::vector<Renderable2D*>(); }

	};
}