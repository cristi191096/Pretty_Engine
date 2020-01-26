#pragma once
#include "Texture.h"
#include "Types.h"

namespace PrettyEngine {

		class PE_API Texture2D : public Texture
	{
	public:
		virtual void SetData(const void* pixels) = 0;
		virtual void SetData(uint color) = 0;

		virtual const TextureParameters& GetParameters() const = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
	public:
		static Texture2D* Create(uint width, uint height, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		static Texture2D* CreateFromFile(const String& filepath, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		static Texture2D* CreateFromFile(const String& filepath, TextureLoadOptions loadOptions);
		static Texture2D* CreateFromFile(const String& name, const String& filepath, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		static Texture2D* CreateFromFile(const String& name, const String& filepath, TextureLoadOptions loadOptions);

	};

}