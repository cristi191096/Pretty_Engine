#pragma once

#include "engine\Core\Core.h"

#include "Window.h"
#include "engine\Core\LayerStack.h"
#include "engine\Events\Event.h"
#include "engine\Events\ApplicationEvent.h"
#include "engine\Core\Context.h"
#include "Utilities\Profiler.h"

#include "editor\EditorLayer.h"

namespace PrettyEngine {

	class PE_API Application
	{
	public:
		Application(RenderAPI api = RenderAPI::OPENGL);

		virtual ~Application();
		//Run App
		void Run();	

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		inline void ShouldRun(bool run) { m_Running = run; }
		inline void UseEditor(bool use) { m_EditorInUse = use; }
		inline bool EditorInUse() const { return m_EditorInUse; }
		inline void SetGameVisibility(bool* visibility) { m_GameVisibility = visibility; }
		inline EditorLayer* GetEditor() const { return m_EditorLayer; }
		inline std::vector<ProfileResult>* GetProfileResults() { return &m_ProfileResults; }

	private:
		//Event Callbacks
		bool OnWindowClose(WindowCloseEvent& e);

		static Application* s_Instance;

		bool m_EditorInUse;
		bool* m_GameVisibility;
		std::unique_ptr<Window> m_Window;
		EditorLayer* m_EditorLayer;
		std::vector<ProfileResult> m_ProfileResults;

		bool m_Running = true;
		LayerStack m_LayerStack;
	//	std::vector<std::thread> m_Threads;		//Not yet!	Note: DO NOT HAVE DRAW CALLS ON DIFFERENT THREADS!!
	};


	//TO be defined in the CLIENT
	//Application* CreateApplication();

}