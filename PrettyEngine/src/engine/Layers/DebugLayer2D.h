#pragma once
#include "engine\Core\Layer.h"

#include "engine\Core\Core.h"

#include "engine\Events\Event.h"
#include "engine\Events\ApplicationEvent.h"
#include "engine\Events\MouseEvent.h"
#include "engine\Events\KeyEvent.h"

//Test includes 
#include "engine\Graphics\Shaders\Shader.h"

#include "engine\Graphics\Renderer2D.h"
#include "engine\Graphics\Renderable2D.h"

#include "engine\Graphics\Cameras\Camera.h"

//Test includes 
#include "engine\Graphics\Sprite.h"
#include "engine\Graphics\Group.h"
//------------------------

namespace PrettyEngine {

	/*
	Layer used to test different features while developing
	*/
	class PE_API DebugLayer2D : public Layer
	{
	public:
		DebugLayer2D();
		~DebugLayer2D();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		bool OnWindowCloseEvent(WindowCloseEvent& e);

	private:
	

		Renderer2D* renderer;
		std::vector<Renderable2D*> m_Renderables;

		Camera* m_Camera;

	};
}