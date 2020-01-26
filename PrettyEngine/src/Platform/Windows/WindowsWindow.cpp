#include "pepch.h"
#include "WindowsWindow.h"

#include "engine\Events\ApplicationEvent.h"
#include "engine\Events\KeyEvent.h"
#include "engine\Events\MouseEvent.h"

#include "engine\Graphics\Renderer.h"

#include "engine\Core\Context.h"


namespace PrettyEngine {

	
	Window* Window::Create(const WindowProps& props) 
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow() 
	{
		Shutdown();
	}

	void WindowsWindow::SetInputCallbacks()
	{
		Internal::InternalInput::GetInstance()->KeyboardCallback();
		Internal::InternalInput::GetInstance()->CharCallback();
		Internal::InternalInput::GetInstance()->MouseButtonCallback();
		Internal::InternalInput::GetInstance()->MousePositionCallback();
		Internal::InternalInput::GetInstance()->MouseScrollCallback();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		Context::Get()->SetVSync(enabled);
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::OnUpdate()
	{
		Context::Get()->Update();
	}

	void WindowsWindow::Init(const WindowProps & props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		PE_CORE_INFO("Creating Window {0}: ({1}, {2})", props.Title, props.Width, props.Height);

		Context::Create(m_Data);

		Internal::InternalInput::Init();
		Internal::InternalInput::SetEventCallback(m_Data.EventCallback);

		Renderer::Init();
	}

	void WindowsWindow::Shutdown()
	{
		Context::Get()->Destroy();
	}


}