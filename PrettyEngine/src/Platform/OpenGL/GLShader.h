#pragma once

#include "engine\Graphics\Shaders\Shader.h"
#include "engine\Graphics\Shaders\ShaderManager.h"
#include "GLCore.h"

namespace PrettyEngine {

	struct GLShaderErrorInfo
	{
		uint shader;
		String message[2];
		uint line[2];
	};

	class GLShader : public Shader
	{
		enum class ShaderType {
			UNKNOWN = -1, VERTEX = 0, FRAGMENT = 1
		};


	public:
		GLShader(const String& name, const String& source);
		~GLShader();

		void Bind() const override;
		void Unbind() const override;

		void const SetFilePath(const String& path) override;
		//virtual void SetType(const Type& type) override;

		inline const String& GetName() const override { return m_Name; }
		inline const Type& GetType() const override { return m_Type; }
		inline const String& GetFilePath() const override { return m_Path; }
		inline const BufferLayout& GetLayout() const override { return m_Layout; }

	private:
		uint m_ID;
		String m_Name;
		String m_Path = "None";
		String m_Source;
		String m_VertexSource, m_FragmentSource;
		BufferLayout m_Layout;
		Type m_Type;

	private:
		friend class Shader;
		friend class ShaderManager;

	private:
		void Init();
		void ShutDown();
		Type ConvertNameToType();
		const String& ConvertTypeToName();
		void Process(const String& source, String** shaders);
		void SetLayout(const String& line);
		uint Compile(String** shaders, GLShaderErrorInfo& info);
		GLint GetUniformLocation(const String& name);

	public:
		void SetUniform1f(const String& name, float value);
		void SetUniform1fv(const String& name, float* value, int count);
		void SetUniform1i(const String& name, int value);
		void SetUniform1iv(const String& name, int* value, int count);
		void SetUniform2f(const String& name, const Vector2& vector);
		void SetUniform3f(const String& name, const Vector3& vector);
		void SetUniform4f(const String& name, const Vector4& vector);
		void SetUniformMat4(const String& name, const Matrix4& matrix);

	private:
		void SetUniform1f(uint location, float value);
		void SetUniform1fv(uint location, float* value, int count);
		void SetUniform1i(uint location, int value);
		void SetUniform1iv(uint location, int* value, int count);
		void SetUniform2f(uint location, const Vector2& vector);
		void SetUniform3f(uint location, const Vector3& vector);
		void SetUniform4f(uint location, const Vector4& vector);
		void SetUniformMat4(uint location, const Matrix4& matrix);

	};

	

}