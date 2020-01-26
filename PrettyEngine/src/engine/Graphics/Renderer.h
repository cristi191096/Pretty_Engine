#pragma once

#include "engine\Core\Core.h"
#include "engine\Maths\Vector4.h"

namespace PrettyEngine {

	enum PE_API RendererBufferType
	{
		NA		= 0,
		COLOR		= BIT(0),
		DEPTH		= BIT(1),
		STENCIL		= BIT(2)
	};

	enum class PE_API RendererBlendFunction
	{
		NONE,
		ZERO,
		ONE,
		SOURCE_ALPHA,
		DESTINATION_ALPHA,
		ONE_MINUS_SOURCE_ALPHA
	};

	enum class PE_API RendererBlendEquation
	{
		NONE,
		ADD,
		SUBTRACT,
		REVERSESUBSTRACT,
		MIN,
		MAX
	};



	class PE_API Renderer 
	{
	public:
		static void  Init();
		inline static Renderer* Get() { return s_Instance; }

	public:
		inline static void Clear(uint buffer) { s_Instance->ClearInternal(buffer); }
		inline static void ClearColour(Vector4 colour) { s_Instance->ClearColourInternal(colour); }

		inline static void SetDepthTesting(bool enabled) { s_Instance->SetDepthTestingInternal(enabled); }
		inline static void SetBlend(bool enabled) { s_Instance->SetBlendInternal(enabled); }
		inline static void SetViewport(uint x, uint y, uint width, uint height) { s_Instance->SetViewportInternal(x, y, width, height); }

		inline static void SetBlendFunction(RendererBlendFunction source, RendererBlendFunction destination) { s_Instance->SetBlendFunctionInternal(source, destination); }
		inline static void SetBlendEquation(RendererBlendEquation blendEquation) { s_Instance->SetBlendEquationInternal(blendEquation); }

	protected:
		virtual void InitInternal() = 0;
		virtual void ClearInternal(uint buffer) = 0;
		virtual void ClearColourInternal(Vector4 colour) = 0;

		virtual void SetDepthTestingInternal(bool enabled) = 0;
		virtual void SetBlendInternal(bool enabled) = 0;
		virtual void SetViewportInternal(uint x, uint y, uint width, uint height) = 0;

		virtual void SetBlendFunctionInternal(RendererBlendFunction source, RendererBlendFunction destination) = 0;
		virtual void SetBlendEquationInternal(RendererBlendEquation blendEquation) = 0;

	private:
		static Renderer* s_Instance;

	};
}