#include "pepch.h"
#include "GLContext.h"
#include "engine/Events/ApplicationEvent.h"

namespace PrettyEngine {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		PE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}


	GLContext::GLContext(Window::WindowData& properties)
	{
		if (!s_GLFWInitialized)
		{
			//TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			PE_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			m_WindowData = &properties;
			s_GLFWInitialized = true;
		}

		m_ContextWindow = glfwCreateWindow((int)m_WindowData->Width, (int)m_WindowData->Height, m_WindowData->Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_ContextWindow);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PE_CORE_ASSERT(status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(m_ContextWindow, m_WindowData);
		SetVSync(true);
		m_WindowData->VSync = m_VSync;

		//Set GLFW callbacks
		glfwSetWindowSizeCallback(m_ContextWindow, [](GLFWwindow* window, int width, int height) 
		{
			Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent ev(width, height);
			data.EventCallback(ev);
		});

		glfwSetWindowCloseCallback(m_ContextWindow, [](GLFWwindow* window) 
		{
			Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent ev;
			data.EventCallback(ev);
		});


	}

	void GLContext::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_ContextWindow);
	}
	void GLContext::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		
		 m_VSync = enabled;
	}
	bool GLContext::GetVSync() const
	{
		return m_VSync;
	}
	void GLContext::Destroy() const
	{
		glfwDestroyWindow((GLFWwindow*)m_ContextWindow);
	}
	void * GLContext::GetNativeContext() const
	{
		return m_ContextWindow;
	}
}