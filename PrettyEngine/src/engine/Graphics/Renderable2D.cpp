#include "pepch.h"
#include "Renderable2D.h"

namespace PrettyEngine {

	Renderable2D::Renderable2D(const Vector3 & position, const Vector2 & size, uint color)
		: m_Position(position), m_Size(size), m_Color(color), m_Texture(nullptr), m_Visible(true)
	{	
	
		m_UVs = GetDefaultUVs();
	}

	void Renderable2D::SetColor(const Vector4 & color)
	{
		uint r = (uint)(color.x * 255.0f);
		uint g = (uint)(color.y * 255.0f);
		uint b = (uint)(color.z * 255.0f);
		uint a = (uint)(color.w * 255.0f);

		m_Color = a << 24 | b << 16 | g << 8 | r;
	}

	void Renderable2D::Submit(Renderer2D * renderer) const
	{
		renderer->Submit(this);
	}

	Renderable2D::Renderable2D()
		:m_Color(0xffffffff), m_Texture(nullptr), m_Visible(true)
	{
		m_UVs = GetDefaultUVs();
	}

	const std::vector<Vector2>& Renderable2D::GetDefaultUVs()
	{
		 static std::vector<Vector2> results;
		
			results.push_back(Vector2(0, 0));
			results.push_back(Vector2(1, 0));
			results.push_back(Vector2(1, 1));
			results.push_back(Vector2(0, 1));
		
		return results;
	}

}