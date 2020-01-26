#pragma once
#include "engine\Core\Core.h"


namespace PrettyEngine {

	
	enum class PE_API TextureType {
		None = 0,
		Diffuse,
		Specular,
		Normal,
		Emissive,
		Height,
		Roughness,
	};


	enum class PE_API TextureWrap
	{
		NONE = 0,
		REPEAT,
		MIRRORED_REPEAT,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER
	};

	enum class PE_API TextureFilter
	{
		NONE = 0,
		LINEAR,
		NEAREST
	};

	enum class PE_API TextureFormat
	{
		NONE = 0,
		RGB,
		RGBA,
		LUMINANCE,
		LUMINANCE_ALPHA
	};


	// ^ Container for the above ones ^
	struct PE_API TextureParameters
	{
		TextureFormat format;
		TextureFilter filter;
		TextureWrap wrap;
		TextureType type;

		TextureParameters()
		{
			format = TextureFormat::RGBA;
			filter = TextureFilter::LINEAR;
			wrap = TextureWrap::CLAMP_TO_EDGE;
			type = TextureType::Diffuse;
		}

		TextureParameters(TextureFormat format, TextureFilter filter, TextureWrap wrap, TextureType type)
			: format(format), filter(filter), wrap(wrap), type(type)
		{
		}

		TextureParameters(TextureFormat format, TextureFilter filter, TextureWrap wrap)
			: format(format), filter(filter), wrap(wrap), type(TextureType::Diffuse)
		{
		}

		TextureParameters(TextureWrap wrap, TextureType type)
			: format(TextureFormat::RGBA), filter(TextureFilter::LINEAR), wrap(wrap), type(type)
		{
		}

		TextureParameters(TextureType type)
			: format(TextureFormat::RGBA), filter(TextureFilter::LINEAR), wrap(TextureWrap::CLAMP_TO_EDGE), type(type)
		{
		}

		TextureParameters(TextureFilter filter)
			: format(TextureFormat::RGBA), filter(filter), wrap(TextureWrap::CLAMP_TO_EDGE), type(TextureType::Diffuse)
		{
		}

		TextureParameters(TextureFilter filter, TextureWrap wrap)
			: format(TextureFormat::RGBA), filter(filter), wrap(wrap), type(TextureType::Diffuse)
		{
		}
	};

	struct PE_API TextureLoadOptions
	{
		bool flipX;
		bool flipY;

		TextureLoadOptions()
		{
			flipX = false;
			flipY = false;
		}

		TextureLoadOptions(bool flipX, bool flipY)
			: flipX(flipX), flipY(flipY)
		{
		}
	};

	class Texture
	{
	protected:
		static TextureWrap s_WrapMode;
		static TextureFilter s_FilterMode;

	public:
		virtual ~Texture() {}

		virtual void Bind(uint slot = 0) const = 0;
		virtual void Unbind(uint slot = 0) const = 0;

		virtual const String& GetName() const = 0;
		virtual const String& GetFilepath() const = 0;

	public:
		inline static void SetWrap(TextureWrap mode) { s_WrapMode = mode; }
		inline static void SetFilter(TextureFilter mode) { s_FilterMode = mode; }
	public:
		static byte GetStrideFromFormat(TextureFormat format);

	};



	
}