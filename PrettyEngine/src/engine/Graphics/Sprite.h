#pragma once
#include "engine\Core\Core.h"
#include "Renderable2D.h"

#include "Texture2D.h"

namespace PrettyEngine {

	class PE_API Sprite : public Renderable2D
	{
	protected:
		Sprite();
	public:
		Sprite(Texture2D* texture);
		Sprite(float x, float y, Texture2D* texture);
		Sprite(float x, float y, float width, float height, uint color);
		Sprite(float x, float y, float width, float height, const Vector4& color);
		//Sprite(float x, float y, float width, float height, const Vector4& color, Shader* shader);
		Sprite(float x, float y, float width, float height, Texture* texture);

		void SetUV(const std::vector<Vector2>& uv);

		inline void SetTexture(Texture2D* texture) { m_Texture = texture; }
	};
}