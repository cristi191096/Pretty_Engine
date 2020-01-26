#pragma once

namespace PrettyEngine {

	class ShaderUniform
	{
	public:
		enum class Type
		{
			NONE, FLOAT32, VEC2, VEC3, VEC4, MAT3, MAT4, INT32, STRUCT
		};

	public:
		ShaderUniform();
		~ShaderUniform();

	
	private:
		String m_Name;
		uint m_Size;
		uint m_Count;
		uint m_Offset;

	};

	class ShaderResource
	{
	public:
		enum class Type
		{
			NONE, TEXTURE2D, TEXTURECUBE, TEXTURESHADOW
		};
	public:
		ShaderResource();
		~ShaderResource();

	private:
		String m_Name;
		uint m_Register;
		uint m_Count;
		Type m_Type;
	};



}