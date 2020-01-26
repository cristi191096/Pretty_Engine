#pragma once
#include "engine\Core\Layer.h"

#include "engine\Core\Core.h"

#include "engine\Events\Event.h"
#include "engine\Events\ApplicationEvent.h"
#include "engine\Events\MouseEvent.h"
#include "engine\Events\KeyEvent.h"
#include "engine\Events\PlayerControllerEvent.h"

//Test includes 


//Test includes 
#include "engine\Graphics\Sprite.h"
#include "engine\Graphics\Group.h"
//------------------------

namespace PrettyEngine {

	class Entity;
	class Rigidbody;

	/*
	Layer used to test different features while developing
	*/
	class PE_API DebugLayer3D : public Layer
	{
	public:
		DebugLayer3D();
		~DebugLayer3D();

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
		bool OnJump(JumpEvent& e);
		bool OnMove(MoveEvent& e);

	private:
		Entity* object;
		Rigidbody* objectRB;
		Entity* dirlight;

	};
}