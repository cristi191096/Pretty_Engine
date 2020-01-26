#include "pepch.h"
#include "Texture.h"


namespace PrettyEngine {

	TextureWrap Texture::s_WrapMode = TextureWrap::CLAMP_TO_EDGE;
	TextureFilter Texture::s_FilterMode = TextureFilter::LINEAR;

	byte Texture::GetStrideFromFormat(TextureFormat format)
	{
		switch (format)
		{
			case TextureFormat::RGB:				return 3;
			case TextureFormat::RGBA:				return 4;
			case TextureFormat::LUMINANCE_ALPHA:	return 4;
		}
		return 0;
	}

}