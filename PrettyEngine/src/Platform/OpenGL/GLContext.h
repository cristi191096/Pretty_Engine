#pragma once

#include "engine\Core\Context.h"
#include "GLFW\glfw3.h"
#include "glad\glad.h"

namespace PrettyEngine {

	class GLContext : public Context
	{
	public:
		GLContext(Window::WindowData& properties);

		void Update() override;
	public:
		void SetVSync(bool enabled) override;
		bool GetVSync() const override;
		void Destroy() const override;
		virtual void* GetNativeContext() const override;

	private:
		bool m_VSync;
		GLFWwindow* m_ContextWindow;
		Window::WindowData* m_WindowData;
	};
}