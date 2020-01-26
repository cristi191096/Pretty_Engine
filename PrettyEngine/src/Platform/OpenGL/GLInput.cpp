
#include "pepch.h"
#include "GLInput.h"

#include "engine\Core\Window.h"

#include "engine\Events\ApplicationEvent.h"
#include "engine\Events\KeyEvent.h"
#include "engine\Events\MouseEvent.h"
#include "engine\Events\PlayerControllerEvent.h"


namespace PrettyEngine { namespace Internal {

		static int s_CountRepeats = 0;
	
		void GLInput::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
		{
			
			Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
			m_Mods = mods;
				switch (action)
				{
				case action::Press:
					{
						m_Keys[key] = true;
						KeyPressedEvent ev1(key, 0);
						data.EventCallback(ev1);
						switch (key)
						{
						case KeyBinds::Jump: 
						{
							JumpEvent jump;
							data.EventCallback(jump);
							break;
						}
						case KeyBinds::MoveLeft:
						{
							MoveEvent move(-1);
							data.EventCallback(move);
							break;
						}
						case KeyBinds::MoveRight:
						{
							MoveEvent move(1);
							data.EventCallback(move);
							break;
						}
						case KeyBinds::Attack:
						{
							AttackEvent attack;
							data.EventCallback(attack);
							break;
						}
						case KeyBinds::Block:
						{
							BlockEvent block;
							data.EventCallback(block);
							break;
						}
						case keyCode::Escape:
						{
							WindowCloseEvent closeEv;
							data.EventCallback(closeEv);
							break;
						}
						default:
							break;
						}
						break;
					}

				case action::Repeat: 
					{
						m_Keys[key] = true;
						KeyPressedEvent ev2(key, s_CountRepeats);
						data.EventCallback(ev2);
						s_CountRepeats++;

						switch (key)
						{
						case KeyBinds::MoveLeft:
						{
							MoveEvent move(-1);
							data.EventCallback(move);
							break;
						}
						case KeyBinds::MoveRight:
						{
							MoveEvent move(1);
							data.EventCallback(move);
							break;
						}
						case KeyBinds::Block:
						{
							BlockEvent block;
							data.EventCallback(block);
							break;
						}
						default:
							break;
						}
						break;
					}
				case action::Release: 
					{
						m_Keys[key] = false;
						KeyReleasedEvent ev3(key);
						data.EventCallback(ev3);
						s_CountRepeats = 0;
						break;
					}
				}
		}

		void GLInput::char_callback(GLFWwindow * window, unsigned int keycode)
		{
			Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		}

		void GLInput::mouseButton_callback(GLFWwindow * window, int button, int action, int mods)
		{
			Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case action::Press:
				{
					m_MouseButtons[button] = true;
					MouseButtonPressedEvent ev(button);
					data.EventCallback(ev);
					break;
				}

				case action::Release:
				{
					m_MouseButtons[button] = false;
					MouseButtonReleasedEvent ev(button);
					data.EventCallback(ev);
					break;
				}
			}
		}

		void GLInput::mousePos_callback(GLFWwindow * window, double xPos, double yPos)
		{
			Vector2 mousePos = Vector2((float)xPos, (float)yPos);
			if (mousePos != m_MousePosition)
			{
				Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent ev(xPos, yPos);
				data.EventCallback(ev);
				m_MousePosition = mousePos;
			}
		}

		void GLInput::mouseScroll_callback(GLFWwindow * window, double xOffset, double yOffset)
		{			
			Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent ev(xOffset, yOffset);
			data.EventCallback(ev);
		}


		void GLInput::KeyboardCallback()
		{
			glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);
		}

		

		void GLInput::MouseButtonCallback()
		{
			glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouseButton_callback);
		}

		void GLInput::MouseScrollCallback()
		{
			glfwSetScrollCallback(glfwGetCurrentContext(), mouseScroll_callback);
		}

		void GLInput::MousePositionCallback()
		{
			glfwSetCursorPosCallback(glfwGetCurrentContext(), mousePos_callback);
		}

		void GLInput::CharCallback()
		{
			glfwSetCharCallback(glfwGetCurrentContext(), char_callback);
		}

		GLInput::GLInput() : InternalInput()
		{
			s_CountRepeats = 0;
		}

		GLInput::~GLInput()
		{
		}

	}
}

