#pragma once

#include "pepch.h"
#include "engine\Core\Core.h"
#include "engine\Events\Event.h"


namespace PrettyEngine {

	struct  WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Pretty Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) 
		{
		}
	};

	//Desktop based Window
	class PE_API Window 
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;	// Used for binding the Events from glfw to the Event Queue
		
		struct WindowData 
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetInputCallbacks() = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}
