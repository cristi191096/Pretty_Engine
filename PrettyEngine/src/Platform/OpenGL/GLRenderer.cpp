#include "pepch.h"
#include "GLCore.h"
#include "GLRenderer.h"

namespace PrettyEngine {

	uint GLRenderer::RendererBufferToGL(uint buffer)
	{
		uint result = 0;
		if (buffer & COLOR)
			result |= GL_COLOR_BUFFER_BIT;
		if (buffer & DEPTH)
			result |= GL_DEPTH_BUFFER_BIT;
		if (buffer & STENCIL)
			result |= GL_STENCIL_BUFFER_BIT;
		return result;
	}

	uint GLRenderer::RendererBlendFunctionToGL(RendererBlendFunction function)
	{
		switch (function)
		{
			case RendererBlendFunction::ZERO:						return GL_ZERO;
			case RendererBlendFunction::ONE:						return GL_ONE;
			case RendererBlendFunction::SOURCE_ALPHA:				return GL_SRC_ALPHA;
			case RendererBlendFunction::DESTINATION_ALPHA:			return GL_DST_ALPHA;
			case RendererBlendFunction::ONE_MINUS_SOURCE_ALPHA:		return GL_ONE_MINUS_SRC_ALPHA;
		}
		return 0;
	}

	uint GLRenderer::RendererBlendEquationToGL(RendererBlendEquation equation)
	{
		switch (equation)
		{
		case RendererBlendEquation::ADD:				return GL_FUNC_ADD;
		case RendererBlendEquation::SUBTRACT:			return GL_FUNC_SUBTRACT;
		case RendererBlendEquation::REVERSESUBSTRACT:	return GL_FUNC_REVERSE_SUBTRACT;
		case RendererBlendEquation::MIN:				return GL_MIN;
		case RendererBlendEquation::MAX:				return GL_MAX;
		}
		return 0;
	}


	GLRenderer::GLRenderer()
	{

	}

	GLRenderer::~GLRenderer()
	{
	}

	void GLRenderer::InitInternal()
	{
		SetDepthTesting(true);
		SetBlendInternal(true);
		SetBlendFunctionInternal(RendererBlendFunction::SOURCE_ALPHA, RendererBlendFunction::ONE_MINUS_SOURCE_ALPHA);


		//TODO: Abstract culling, make it flexible for the user
		GLCall(glEnable(GL_CULL_FACE));
		GLCall(glFrontFace(GL_CCW));
		GLCall(glCullFace(GL_BACK));
	}


	void GLRenderer::ClearInternal(uint buffer)
	{
		GLCall(glClear(RendererBufferToGL(buffer)));
	}

	void GLRenderer::ClearColourInternal(Vector4 colour)
	{
		GLCall(glClearColor(colour.x, colour.y, colour.z, colour.w));
	}

	void GLRenderer::SetDepthTestingInternal(bool enabled)
	{
		if (enabled) 
		{
			GLCall(glEnable(GL_DEPTH_TEST));
		}
		else
		{
			GLCall(glDisable(GL_DEPTH_TEST));
		}
	}

	void GLRenderer::SetBlendInternal(bool enabled)
	{
		if (enabled) 
		{
			GLCall(glEnable(GL_BLEND));
		}
		else
		{
			GLCall(glDisable(GL_BLEND));
		}
	}

	void GLRenderer::SetViewportInternal(uint x, uint y, uint width, uint height)
	{
		GLCall(glViewport(x, y, width, height));
	}

	void GLRenderer::SetBlendFunctionInternal(RendererBlendFunction source, RendererBlendFunction destination)
	{
		GLCall(glBlendFunc(RendererBlendFunctionToGL(source), RendererBlendFunctionToGL(destination)));
	}

	void GLRenderer::SetBlendEquationInternal(RendererBlendEquation blendEquation)
	{
		GLCall(glBlendEquation(RendererBlendEquationToGL(blendEquation)));
	}

	

}