#include "pepch.h"
#include "GLTexture2D.h"
#include "GLCore.h"

#include "Utilities\Imagery.h"



namespace PrettyEngine {
	GLTexture2D::GLTexture2D(uint width, uint height, TextureParameters parameters, TextureLoadOptions loadOptions)
		: m_FileName("NULL")
	{
		m_Width = width;
		m_Height = height;
		m_Parameters = parameters;
		m_LoadOptions = loadOptions;
		m_ID = Generate();
	}
	GLTexture2D::GLTexture2D(uint width, uint height, uint color, TextureParameters parameters, TextureLoadOptions loadOptions)
		: m_FileName("NULL")
	{
		m_Width = width;
		m_Height = height;
		m_Parameters = parameters;
		m_LoadOptions = loadOptions;
		m_ID = Generate(color);
	}
	GLTexture2D::GLTexture2D(const String & name, const String & filename, TextureParameters parameters, TextureLoadOptions loadOptions)
		: m_FileName(filename)
	{
		m_Name = name;
		m_Parameters = parameters;
		m_LoadOptions = loadOptions;
		m_ID = Load();
	}
	GLTexture2D::~GLTexture2D()
	{
		GLCall(glDeleteTextures(1, &m_ID));
	}
	void GLTexture2D::Bind(uint slot) const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
	}
	void GLTexture2D::Unbind(uint slot) const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
	void GLTexture2D::SetData(const void * pixels)
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
		GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, TextureFormatToGL(m_Parameters.format), GL_UNSIGNED_BYTE, pixels));
	}
	void GLTexture2D::SetData(uint color)
	{
		PE_CORE_ASSERT(false, "Broken");
		uint stride = m_Parameters.format == TextureFormat::RGB ? 3 : 4;
		uint size = m_Width * m_Height * stride;
		byte* data = new byte[size];
		for (uint i = 0; i < size; i += stride)
		{
			data[i + 0] = (color & 0xff);
			data[i + 1] = (color & 0xff00) >> 8;
			data[i + 2] = (color & 0xff0000) >> 16;
			if (stride == 4)
				data[i + 3] = (color & 0xff000000) >> 24;
		}

		SetData(data);
		delete[] data;
	}
	uint GLTexture2D::TextureFormatToGL(TextureFormat format)
	{
		switch (format)
		{
			case TextureFormat::RGBA:				return GL_RGBA;
			case TextureFormat::RGB:				return GL_RGB;
			case TextureFormat::LUMINANCE:			return GL_RED;
			case TextureFormat::LUMINANCE_ALPHA:	return GL_RG;
		}
		return 0;
	}
	uint GLTexture2D::TextureInternalFormatToGL(TextureFormat format)
	{
		switch (format)
		{
			case TextureFormat::RGBA:				return GL_RGBA8;
			case TextureFormat::RGB:				return GL_RGB8;
			case TextureFormat::LUMINANCE:			return GL_R8;
			case TextureFormat::LUMINANCE_ALPHA:	return GL_RG8;
		}
		return 0;
	}
	uint GLTexture2D::TextureWrapToGL(TextureWrap wrap)
	{
			switch (wrap)
		{
			case TextureWrap::CLAMP_TO_BORDER:	return GL_CLAMP_TO_BORDER;
			case TextureWrap::CLAMP_TO_EDGE:	return GL_CLAMP_TO_EDGE;
			case TextureWrap::REPEAT:			return GL_REPEAT;
			case TextureWrap::MIRRORED_REPEAT:	return GL_MIRRORED_REPEAT;
		}
		return 0;
	}
	
	uint GLTexture2D::Load()
	{
		unsigned char* pixels = nullptr;
		if (m_FileName != "NULL")
		{
			PE_CORE_INFO("FileName: {0}", m_FileName);
			int bits;	//BPP or BitsPerPixel
			pixels = LoadImage(m_FileName, &m_Width, &m_Height, &bits, m_LoadOptions.flipY); // stb loads bottom->top
			if (pixels == nullptr)
				PE_CORE_TRACE("Failed to load texture");
			if (bits != 3 &&  bits != 4)		//Only supports RGBA. TODO: Find solutions
				PE_CORE_ERROR("[Texture] Unsupported image bit-depth! ( {0} )", bits);
			m_Parameters.format = bits == 3 ? TextureFormat::RGB : TextureFormat::RGBA;		// OpenGL doesn't like RGB format. idk why?
		}
		//for (int i = 0; i < m_Width*m_Height; i++) {
		//	if (m_Parameters.format == TextureFormat::RGB) {
		//		std::cout << (int)pixels[i] << " " << (int)pixels[i + 1] << " " << (int)pixels[i + 2] << std::endl;
		//	}
		//	else
		//	{
		//		std::cout << (int)pixels[i] << " " << (int)pixels[i + 1] << " " << (int)pixels[i + 2] << " " << (int)pixels[i + 3] << std::endl;
		//	}
		//	
		//}
		
		GLCall(glEnable(GL_TEXTURE_2D));
		
		uint handle;
		GLCall(glGenTextures(1, &handle));

		if (pixels != nullptr) {
			GLCall(glBindTexture(GL_TEXTURE_2D, handle));

			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, TextureInternalFormatToGL(m_Parameters.format), m_Width, m_Height, 0, TextureFormatToGL(m_Parameters.format), GL_UNSIGNED_BYTE, pixels ? pixels : NULL));
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));

			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_Parameters.filter == TextureFilter::LINEAR ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_Parameters.filter == TextureFilter::LINEAR ? GL_LINEAR : GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToGL(s_WrapMode)));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToGL(s_WrapMode)));

			GLCall(glBindTexture(GL_TEXTURE_2D, 0));


			FreeImageData(pixels);

			GLCall(glDisable(GL_TEXTURE_2D));

			return handle;
		}
		PE_CORE_ERROR("Failed to load texture at path: {0}", m_FileName);
		return 0;
	}
	uint GLTexture2D::Generate(uint pixelData)
	{
		byte* pixels = nullptr;
		
		uint stride = m_Parameters.format == TextureFormat::RGB ? 3 : 4;
		uint size = m_Width * m_Height * stride;
		pixels = new byte[size];
		for (uint i = 0; i < size; i += stride)
		{
			pixels[i + 0] = (pixelData & 0xff);
			pixels[i + 1] = (pixelData & 0xff00) >> 8;
			pixels[i + 2] = (pixelData & 0xff0000) >> 16;
			if (stride == 4)
				pixels[i + 3] = (pixelData & 0xff000000) >> 24;
		}
		
		uint handle;
		GLCall(glGenTextures(1, &handle));
		GLCall(glBindTexture(GL_TEXTURE_2D, handle));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_Parameters.filter == TextureFilter::LINEAR ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_Parameters.filter == TextureFilter::LINEAR ? GL_LINEAR : GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToGL(s_WrapMode)));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToGL(s_WrapMode)));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, TextureInternalFormatToGL(m_Parameters.format), m_Width, m_Height, 0, TextureFormatToGL(m_Parameters.format), GL_UNSIGNED_BYTE, pixels ? pixels : NULL));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		if (pixels != nullptr)
			delete[] pixels;

		return handle;
	}
}