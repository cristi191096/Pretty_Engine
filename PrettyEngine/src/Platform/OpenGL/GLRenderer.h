#pragma once
#include "engine\Graphics\Renderer.h"


namespace PrettyEngine {

	class GLRenderer : public Renderer
	{
	public:
		GLRenderer();
		~GLRenderer();

	protected:

		virtual void InitInternal() override;
		virtual void ClearInternal(uint buffer) override;
		virtual void ClearColourInternal(Vector4 colour) override;

		virtual void SetDepthTestingInternal(bool enabled) override;
		virtual void SetBlendInternal(bool enabled) override;
		virtual void SetViewportInternal(uint x, uint y, uint width, uint height) override;

		virtual void SetBlendFunctionInternal(RendererBlendFunction source, RendererBlendFunction destination) override;
		virtual void SetBlendEquationInternal(RendererBlendEquation blendEquation) override;

	private:
			static uint RendererBufferToGL(uint buffer);
			static uint RendererBlendFunctionToGL(RendererBlendFunction function);
			static uint RendererBlendEquationToGL(RendererBlendEquation equation);

	};

	
}