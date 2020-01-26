#include "pepch.h"
#include "Sprite.h"

namespace PrettyEngine {

	Sprite::Sprite()
		: Renderable2D()
	{
	}

		Sprite::Sprite(Texture2D* texture)
		: Renderable2D(Vector3(0.0f, 0.0f, 0.0f), Vector2((float)texture->GetWidth(), (float)texture->GetHeight()), 0xffffffff)
	{
		m_Texture = texture;
	}

	Sprite::Sprite(float x, float y, Texture2D* texture)
		: Renderable2D(Vector3(x, y, 0.0f), Vector2((float)texture->GetWidth(), (float)texture->GetHeight()), 0xffffffff)
	{
		m_Texture = texture;
		PE_CORE_TRACE("Texture: {0}", texture->GetName());
	}

	Sprite::Sprite(float x, float y, float width, float height, uint color)
		: Renderable2D(Vector3(x, y, 0.0f), Vector2(width, height), color)
	{
	}

	Sprite::Sprite(float x, float y, float width, float height, const Vector4& color)
		: Renderable2D(Vector3(x, y, 0.0f), Vector2(width, height), 0xffffffff)
	{
		SetColor(color);
	}

	Sprite::Sprite(float x, float y, float width, float height, Texture * texture)
		: Renderable2D(Vector3(x, y, 0.0f), Vector2(width, height), 0xffffffff)
	{
		m_Texture = texture;
	}

	void Sprite::SetUV(const std::vector<Vector2>& uv)
	{
		m_UVs = uv;
	}

	
}