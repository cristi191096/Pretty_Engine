#include "pepch.h"
#include "engine\Core\Application.h"
#include "engine\Physics\PhysicsContext.h"
#include "engine\Audio\AudioContext.h"
#include "engine\Networking\NetworkContext.h"
#include "engine\Graphics\Renderer.h"



namespace PrettyEngine {



	Application* Application::s_Instance = nullptr;

	Application::Application(RenderAPI api)
	{
		PE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		//Contexts initialisation
		Context::SetRenderAPI(api);
			

		//Window initialisation
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetInputCallbacks();

		m_EditorLayer = new EditorLayer();		//TODO: Change this to Editor.
		PushOverlay(m_EditorLayer);


		PhysicsContext::Create();
		AudioContext::Create();
		NetworkContext::Create();
		
	}

	
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventHandler handler(e);
		handler.Handle<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
	//	PE_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) 
		{
			(*--it)->OnEvent(e);
			if (e.Handeled)
				break;
		}
	}

	void Application::PushLayer(Layer * layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer * layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	

	void Application::Run() 
	{
		while (m_Running)
		{
			{
				Profiler audioProfile("Audio Update", &m_ProfileResults);
				AudioContext::Get()->Update();
			}
			{
				Profiler drawProfile("Layers Draw Calls", &m_ProfileResults);
				Renderer::ClearColour(Vector4(0.12f, 0.1f, 0.1f, 1.f));
				Renderer::Clear(RendererBufferType::COLOR | RendererBufferType::DEPTH);		// Application should handle this as  there can only be one OpenGL Context

				for (Layer* layer : m_LayerStack)
				{
					if (layer->IsVisible())
						layer->OnUpdate();
				}
			}

			{
				Profiler guiProfile("GUI Update", &m_ProfileResults);
				m_EditorLayer->Begin();
				for (Layer* layer : m_LayerStack)
				{
					if (layer->IsVisible())
						layer->OnImGuiRender();
				}
				m_EditorLayer->End();

			}
			*m_GameVisibility = !m_EditorInUse;

			{
				Profiler physicsProfile("Physics Update", &m_ProfileResults);
				if (!m_EditorInUse)
					PhysicsContext::Get()->Update();
			}

			m_Window->OnUpdate();	
			//for (auto& result : m_ProfileResults)
				

		//	m_ProfileResults.clear();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}