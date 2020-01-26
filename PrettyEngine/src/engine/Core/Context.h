#pragma once

#include "engine\Core\Core.h"
#include "engine\Core\Window.h"

namespace PrettyEngine {


	enum class PE_API RenderAPI
	{
		NONE, OPENGL, DIRECT3D, VULKAN, METAL, WillsAPI
	};

	class PE_API Context
	{
	protected:
		static Context* s_Context;
		static RenderAPI s_RenderAPI;
	public:
		static void Create(Window::WindowData& properties);

		inline static Context* Get() { return s_Context; }

		virtual void Update() = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool GetVSync() const = 0;
		virtual void Destroy() const = 0;
		virtual void* GetNativeContext() const = 0;
		static RenderAPI GetRenderAPI() { return s_RenderAPI; }
		static void SetRenderAPI(RenderAPI api) { s_RenderAPI = api; }
	};
}