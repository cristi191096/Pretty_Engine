#include "pepch.h"
#include "GLShader.h"

#include "Utilities\String.h"

namespace PrettyEngine {

	GLShader::GLShader(const String& name, const String& source)
		: m_Name(name), m_Source(source)
	{
		Init();
		m_Type = ConvertNameToType();
	}

	GLShader::~GLShader()
	{
		//ShutDown();
	}

	void GLShader::Init()
	{
		String* shaders[2] = { &m_VertexSource, &m_FragmentSource };
		Process(m_Source, shaders);
		GLShaderErrorInfo error;
		m_ID = Compile(shaders, error);
		if (!m_ID)
			PE_CORE_ERROR(error.message[error.shader]);
	}

	void GLShader::ShutDown()
	{
		GLCall(glDeleteProgram(m_ID));
	}

	Shader::Type GLShader::ConvertNameToType()
	{
		if (m_Name == "DefaultShader2D") return Type::QUAD2D;
		if (m_Name == "FlatColourShader") return Type::FLAT;
		if (m_Name == "BlinPhongShader") return Type::BLINPHONG;

		return Type::UNKNOWN;

	}

	const String& GLShader::ConvertTypeToName()
	{
		if (m_Type == Type::QUAD2D) return "DefaultShader2D";
		if (m_Type == Type::FLAT) return "FlatColourShader";
		if (m_Type == Type::BLINPHONG) return "BlinPhongShader";

		return "None";

	}

	void GLShader::Process(const String & source, String ** shaders)
	{
		ShaderType type = ShaderType::UNKNOWN;
		std::vector<String> lines = GetLines(source);
		for (uint i = 0; i < lines.size(); i++)
		{
			const char* str = lines[i].c_str();
			if (strstr(str, "#shader")) 
			{
				if (strstr(str, "vertex"))
					type = ShaderType::VERTEX;
				if (strstr(str, "fragment"))
					type = ShaderType::FRAGMENT;
			}
			else if (type != ShaderType::UNKNOWN) 
			{
				if (strstr(str, "layout"))
				{
					SetLayout(str);
				}
				shaders[(int)type]->append(str);
				shaders[(int)type]->append("\n");
			}
		}
	}

	void GLShader::SetLayout(const String& line)
	{
		if (line.find("vec2")!=std::string::npos) 
		{
			std::size_t lastSpace = line.find_last_of(" ");
			std::size_t endOfLine = line.find_last_of(";");
			String name = line.substr(lastSpace + 1, endOfLine - lastSpace - 1);
			m_Layout.Push<Vector2>(name);
		}
		if (line.find("vec3")!=std::string::npos) 
		{
			std::size_t lastSpace = line.find_last_of(" ");
			std::size_t endOfLine = line.find_last_of(";");
			String name = line.substr(lastSpace + 1, endOfLine - lastSpace - 1);
			m_Layout.Push<Vector3>(name);
		}
		if (line.find("vec4")!=std::string::npos) 
		{
			std::size_t lastSpace = line.find_last_of(" ");
			std::size_t endOfLine = line.find_last_of(";");
			String name = line.substr(lastSpace + 1, endOfLine - lastSpace - 1);
			if (line.find("color") != std::string::npos)
			{
				m_Layout.Push<byte>(name, 4, true);
				//m_Layout.Push<Vector4>(name);
			}
			else 
			{
				m_Layout.Push<Vector4>(name);
			}

			
		}
		if (line.find("float")!=std::string::npos) 
		{
			std::size_t lastSpace = line.find_last_of(" ");
			std::size_t endOfLine = line.find_last_of(";");
			String name = line.substr(lastSpace + 1, endOfLine - lastSpace - 1);
			m_Layout.Push<float>(name);
		}
		if (line.find("unsigned int")!=std::string::npos) 
		{
			std::size_t lastSpace = line.find_last_of(" ");
			std::size_t endOfLine = line.find_last_of(";");
			String name = line.substr(lastSpace + 1, endOfLine - lastSpace - 1);
			m_Layout.Push<uint>(name);
		}
	}

	uint GLShader::Compile(String ** shaders, GLShaderErrorInfo & info)
	{
		const char* vertexSource = shaders[(int)ShaderType::VERTEX]->c_str();
		const char* fragmentSource = shaders[(int)ShaderType::FRAGMENT]->c_str();

		GLCall(uint program = glCreateProgram());
		GLCall(GLuint vert = glCreateShader(GL_VERTEX_SHADER));
		GLCall(GLuint frag = glCreateShader(GL_FRAGMENT_SHADER));

		//#VERTEX
		GLCall(glShaderSource(vert, 1, &vertexSource, NULL));
		GLCall(glCompileShader(vert));

			//Compile Logging
		GLint result;
		GLCall(glGetShaderiv(vert, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE) 
		{
			GLint length;
			GLCall(glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &length));
			std::vector<char> error(length);
			GLCall(glGetShaderInfoLog(vert, length, &length, &error[0]));
			String errorMessage(&error[0]);
			info.shader = (uint)ShaderType::VERTEX;
			info.message[info.shader] += "Failed to compile vertex shader!\n";
			info.message[info.shader] += errorMessage;
			GLCall(glDeleteShader(vert));
			return 0;
		}

			//#FRAGMENT
		GLCall(glShaderSource(frag, 1, &fragmentSource, NULL));
		GLCall(glCompileShader(frag));

					//Compile Logging
		GLCall(glGetShaderiv(frag, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE) 
		{
			GLint length;
			GLCall(glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &length));
			std::vector<char> error(length);
			GLCall(glGetShaderInfoLog(frag, length, &length, &error[0]));
			String errorMessage(&error[0], length);
			int lineNumber;
			sscanf(&error[0], "%*s %*d:%d", &lineNumber);
			info.shader = (uint)ShaderType::FRAGMENT;
			info.message[info.shader] += "Failed to compile fragment shader!\n";
			info.line[info.shader] = lineNumber;
			info.message[info.shader] += errorMessage;
			GLCall(glDeleteShader(frag));
			return 0;
		}

		GLCall(glAttachShader(program, vert));
		GLCall(glAttachShader(program, frag));

		GLCall(glLinkProgram(program));
		GLint isLinked = 0;
		GLCall(glGetProgramiv(program, GL_LINK_STATUS, &isLinked));
		if(isLinked == GL_FALSE)
		{
		    GLint length = 0;
		    GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
		
		    //The maxLength includes the NULL character
		    std::vector<GLchar> error(length);
		    GLCall(glGetProgramInfoLog(program, length, &length, &error[0]));

			String errorMessage(&error[0], length);
			int lineNumber;
			sscanf(&error[0], "%*s %*d:%d", &lineNumber);
			info.message[info.shader] += "Failed to Link program!\n";
			info.line[info.shader] = lineNumber;
			info.message[info.shader] += errorMessage;
		
		    //The program is useless now. So delete it.
		    GLCall(glDeleteProgram(program));
		
		    //Exit with failure.
		    return 0;
		}
		GLCall(glValidateProgram(program));

	//Think about it
	//	GLCall(glDetachShader(program, vert));
	//	GLCall(glDetachShader(program, frag));

		GLCall(glDeleteShader(vert));
		GLCall(glDeleteShader(frag));

		return program;
	}

	GLint GLShader::GetUniformLocation(const String & name)					// TODO: Cache the uniform location
	{
		GLCall(GLint result = glGetUniformLocation(m_ID, name.c_str()));
		if(result == -1)
			PE_CORE_ERROR("{0}: could not find uniform {1} in shader!", m_Name, name);

		return result;
	}

	void GLShader::Bind() const
	{
		GLCall(glUseProgram(m_ID));
	}

	void GLShader::Unbind() const
	{
		GLCall(glUseProgram(0));
	}

	void const GLShader::SetFilePath(const String & path)
	{
		m_Path = path;
	}

//	void GLShader::SetType(const Type & type)
//	{
//		m_Type = type; 
//		m_Name = ConvertTypeToName();
//	}


	void GLShader::SetUniform1f(const String& name, float value)
	{
		SetUniform1f(GetUniformLocation(name), value);
	}
	void GLShader::SetUniform1fv(const String& name, float* value, int count)
	{
		SetUniform1fv(GetUniformLocation(name), value, count);
	}
	void GLShader::SetUniform1i(const String& name, int value)
	{
		SetUniform1i(GetUniformLocation(name), value);
	}
	void GLShader::SetUniform1iv(const String& name, int* value, int count)
	{
		SetUniform1iv(GetUniformLocation(name), value, count);
	}
	void GLShader::SetUniform2f(const String& name, const Vector2& vector)
	{
		SetUniform2f(GetUniformLocation(name), vector);
	}
	void GLShader::SetUniform3f(const String& name, const Vector3& vector)
	{
		SetUniform3f(GetUniformLocation(name), vector);
	}
	void GLShader::SetUniform4f(const String& name, const Vector4& vector)
	{
		SetUniform4f(GetUniformLocation(name), vector);
	}
	void GLShader::SetUniformMat4(const String& name, const Matrix4& matrix) 
	{
		SetUniformMat4(GetUniformLocation(name), matrix);
	}

	
	void GLShader::SetUniform1f(uint location, float value)
	{
		GLCall(glUniform1f(location, value));
	}

	void GLShader::SetUniform1fv(uint location, float* value, int count)
	{
		GLCall(glUniform1fv(location, count, value));
	}

	void GLShader::SetUniform1i(uint location, int value)
	{
		GLCall(glUniform1i(location, value));
	}

	void GLShader::SetUniform1iv(uint location, int* value, int count)
	{
		GLCall(glUniform1iv(location, count, value));
	}

	void GLShader::SetUniform2f(uint location, const Vector2& Vector)
	{
		GLCall(glUniform2f(location, Vector.x, Vector.y));
	}

	void GLShader::SetUniform3f(uint location, const Vector3& Vector)
	{
		GLCall(glUniform3f(location, Vector.x, Vector.y, Vector.z));
	}

	void GLShader::SetUniform4f(uint location, const Vector4& Vector)
	{
		GLCall(glUniform4f(location, Vector.x, Vector.y, Vector.z, Vector.w));
	}

	void GLShader::SetUniformMat4(uint location, const Matrix4& matrix)
	{
		GLCall(glUniformMatrix4fv(location, 1, GL_TRUE, &matrix.elements[0]));		
	}

}