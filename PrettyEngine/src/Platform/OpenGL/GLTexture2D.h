#pragma once
#include "engine\Graphics\Texture2D.h"

namespace PrettyEngine {
	class GLTexture2D : public Texture2D
	{
	
	public:
		GLTexture2D(uint width, uint height, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		GLTexture2D(uint width, uint height, uint color, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		GLTexture2D(const String& name, const String& filename, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());

		~GLTexture2D();

		void Bind(uint slot = 0) const override;
		void Unbind(uint slot = 0) const override;

		virtual void SetData(const void* pixels) override;
		virtual void SetData(uint color) override;

		inline uint GetID() const { return m_ID; }
		virtual const TextureParameters& GetParameters() const override { return m_Parameters; }

		inline int GetWidth() const override { return m_Width; }
		inline int GetHeight() const override { return m_Height; }

		inline const String& GetName() const override { return m_Name; }
		inline const String& GetFilepath() const override { return m_FileName; }
	
	public:
		static uint TextureFormatToGL(TextureFormat format);
		static uint TextureInternalFormatToGL(TextureFormat format);
		static uint TextureWrapToGL(TextureWrap wrap);

	private:
		String m_Name;
		String m_FileName = "NULL";
		uint m_ID;
		int m_Width, m_Height;
		TextureParameters m_Parameters;
		TextureLoadOptions m_LoadOptions;

	private:
		//Load from file
		uint Load();
		//Generate from data
		uint Generate(uint pixelData = 0xffffffff);
	};

}