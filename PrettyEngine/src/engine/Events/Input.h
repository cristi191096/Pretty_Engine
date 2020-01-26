#pragma once
#include "engine\Events\Event.h"
#include "Platform\OpenGL\GLInputCodes.h"

#include "engine\Maths\Vector2.h"



namespace PrettyEngine {

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

	//enum PE_API Mod
	//{
	//	None = 0,
	//	Shift = BIT(0),
	//	Control = BIT(1),
	//	Alt = BIT(2),
	//	Super = BIT(3),
	//	CapsLock = BIT(4),
	//	NumLock = BIT(5)
	//};

	namespace Internal {

		typedef std::function<void(Event&)> EventCallbackFn ;

		class InternalInput {


		public:
			
			static InternalInput* GetInstance();
			
			static inline void SetEventCallback(const EventCallbackFn& cb) { s_InputInstance->m_EventCallback = cb; }
			static void Init();
			//static void Update();

			virtual void KeyboardCallback() {};
			virtual void CharCallback() {};
			virtual void MouseButtonCallback() {};
			virtual void MouseScrollCallback() {};
			virtual void MousePositionCallback() {};
			virtual const Vector2& GetMousePosition() const;

		protected:
			static bool m_Keys[MAX_KEYS];
			static bool m_MouseButtons[MAX_BUTTONS];
			static uint m_Mods;
			static Vector2 m_MousePosition;
			static InternalInput* s_InputInstance;
			EventCallbackFn m_EventCallback;
			

		protected:
			InternalInput();
			void ClearKeys();
			void ClearButtons();
	
		};
		
	}


	using namespace Internal;

	class PE_API Input : public InternalInput
	{
		//friend class Window;
		//friend class WindowsWindow;
		
	public:
		static bool GetKey(keyCode key);
		static bool GetKeyUp(keyCode key);
		static bool GetKeyDown(keyCode key);
		static bool IsModOn(uint mod);	// Should use Internal::mod

		static bool GetMouseButton(Mouse button);
		static bool GetMouseButtonDown(Mouse button);
		static bool GetMouseButtonUp(Mouse button);	
		inline static const Vector2& GetMousePosition() { return s_InputInstance->GetMousePosition(); }

	private:
		static bool IsKeyPressed(keyCode k);
		static bool IsButtonPressed(Mouse k);
		
	};

	
}

