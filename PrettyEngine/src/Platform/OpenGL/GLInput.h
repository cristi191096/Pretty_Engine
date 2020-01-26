#pragma once

#include "engine\Events\Input.h"
#include <GLFW\glfw3.h>


namespace PrettyEngine { namespace Internal {

	class GLInput : public InternalInput 
	{
	public:
		

		void KeyboardCallback() override;
		void MouseButtonCallback() override;
		void MouseScrollCallback() override;
		void MousePositionCallback() override;
		void CharCallback() override;

		GLInput();
		~GLInput();

	private:
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void char_callback(GLFWwindow* window, unsigned int keycode);
		static void mouseButton_callback(GLFWwindow* window, int button, int action, int mods);
		static void mousePos_callback(GLFWwindow* window, double xPos, double yPos);
		static void mouseScroll_callback(GLFWwindow* window, double xOffset, double yOffset);
	};
}}