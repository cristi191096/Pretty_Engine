#pragma once

#include "engine\Core\Core.h"
#include "engine\Maths\maths.h"
#include "engine\Graphics\Buffers\BufferLayout.h"


namespace PrettyEngine {

	class PE_API Shader {

	
	public:
		enum Type {
			UNKNOWN = 0, QUAD2D, FLAT, BLINPHONG
		};
	
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void const SetFilePath(const String& path) {}
	//	virtual void SetType(const Type& type) = 0;

		virtual const String& GetName() const = 0;
		virtual const Type& GetType() const = 0;
		virtual const String& GetFilePath() const = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		//TEMPORARY -- PERMANENT -- TODO: Parse the shader uniforms then set them accordingly in the renderer.
		virtual void SetUniform1f(const String& name, float value) = 0;
		virtual void SetUniform1fv(const String& name, float* value, int count) = 0;
		virtual void SetUniform1i(const String& name, int value) = 0;
		virtual void SetUniform1iv(const String& name, int* value, int count) = 0;
		virtual void SetUniform2f(const String& name, const Vector2& vector) = 0;
		virtual void SetUniform3f(const String& name, const Vector3& vector) = 0;
		virtual void SetUniform4f(const String& name, const Vector4& vector) = 0;
		virtual void SetUniformMat4(const String& name, const Matrix4& matrix) = 0;
		//-----------------------------

	public:
		static Shader* CreateFromFile(const String& name, const String& filePath);
		static Shader* CreateFromSource(const String& name, const String& source);

		

	};
}