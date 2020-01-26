#pragma once

#include "engine\Core\Window.h"
#include "engine\Events\Input.h"


namespace PrettyEngine {

	

	class WindowsWindow : public Window 
	{
		

	public:

		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		//Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetInputCallbacks() override;
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	protected:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
	//	GLFWwindow* m_Window;
		WindowData m_Data;
	};
}