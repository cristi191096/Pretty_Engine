#pragma once

#include "engine\Core\Core.h"
#include "engine\Events\Event.h"
#include "engine\Core\Scene.h"



namespace PrettyEngine {

	class PE_API Layer
	{
	public:
		Layer(const std::string& name ="Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const bool IsVisible() const { return m_Visible; }
		inline void SetVisibility(bool visible) { m_Visible = visible; }
		inline const std::string& GetName() const { return m_DebugName; }

//#define THREAD(x, ...) m_Thread = std::thread(x, this, __VA_ARGS__);

	//	inline void JoinThread() { m_Thread.join(); }
	//	std::thread m_Thread;
	protected:
		bool m_Visible;
		std::string m_DebugName;
		Scene* m_Scene;

	protected:
		inline Scene* GetScene() const { return m_Scene; }
		

	};
}
