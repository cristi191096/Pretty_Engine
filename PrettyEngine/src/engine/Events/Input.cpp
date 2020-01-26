#include "pepch.h"
#include "Input.h"


#include "engine\Core\Context.h"
#include "Platform\OpenGL\GLInput.h"


namespace PrettyEngine {

	bool InternalInput::m_Keys[MAX_KEYS];
	bool InternalInput::m_MouseButtons[MAX_BUTTONS];
	uint InternalInput::m_Mods = 0;
	Vector2 InternalInput::m_MousePosition = Vector2(0, 0);

	namespace Internal {

		InternalInput* InternalInput::s_InputInstance = nullptr;

		InternalInput::InternalInput()
		{
			ClearKeys();
			ClearButtons();	
		}

		InternalInput * InternalInput::GetInstance()
		{
			return s_InputInstance;
		}

		void InternalInput::Init()
		{
			if (s_InputInstance == nullptr) 
			{
				switch (Context::GetRenderAPI())
				{
				case RenderAPI::OPENGL:
					s_InputInstance = new GLInput();
					break;
				}	
			}
		}

		

		void InternalInput::ClearKeys()
		{
			for (int i = 0; i < MAX_KEYS; i++) {
				m_Keys[i] = false;
			}
		}

		void InternalInput::ClearButtons()
		{
			for (int i = 0; i < MAX_BUTTONS; i++)
				m_MouseButtons[i] = false;
		}	
	}

		const Vector2& InternalInput::GetMousePosition() const
	{
		return m_MousePosition;
	}

	


	bool Input::GetKey(keyCode key)
	{
		return m_Keys[key];
	}

	bool Input::GetKeyUp(keyCode key)
	{
		if (!IsKeyPressed(key))
			return true;

		return false;
	}

	bool Input::GetKeyDown(keyCode key)
	{
		if (IsKeyPressed(key))
			return true;

		return false;
	}

	bool Input::IsModOn(uint mod)
	{
		if (m_Mods & mod)
			return true;

		return false;

	}

	bool Input::GetMouseButton(Mouse button)
	{
		
		return m_MouseButtons[button];
	}

	bool Input::GetMouseButtonDown(Mouse button)
	{
		if (IsButtonPressed(button))
			return true;

		return false;
	}

	bool Input::GetMouseButtonUp(Mouse button)
	{
		if (!IsButtonPressed(button))
			return true;

		return false;
	}

	bool Input::IsKeyPressed(keyCode k)
	{
		if (k >= MAX_KEYS || k == keyCode::NONE)
			return false;

		if (m_Keys[k] == true) {
			return true;
		}

		
		return m_Keys[k];
	}

	bool Input::IsButtonPressed(Mouse b)
	{
		if (b >= MAX_BUTTONS)
			return false;

		return m_MouseButtons[b];
		
	}
}


