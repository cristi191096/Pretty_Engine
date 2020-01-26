#pragma once
#include "engine\Core\Core.h"

#include "engine\Maths\maths.h"
#include "engine\Graphics\Renderer2D.h"
#include "Texture.h"


namespace PrettyEngine {

	struct PE_API VertexData {
		Vector3 position;	// Vertex position			- location 0
		Vector2 uv;			// Texture coordinates (UV)	- location 1
		float tid;			// Texture ID				- location 2
		uint color;			// Vertex colour			- location 3
		//Vector4 color;
	};
	
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)

	class PE_API Renderable2D
	{
	public:
		Renderable2D(const Vector3& position, const Vector2& size, uint color );
		virtual ~Renderable2D() {}

		inline const Vector3& GetPosition() const { return m_Position; }
		inline const Vector2& GetSize() const { return m_Size; }
		inline const uint GetColor() const { return m_Color; }
		inline Texture* GetTexture() const { return m_Texture; }
		inline const std::vector<Vector2>& GetUVs() const { return m_UVs; }
		inline const bool IsVisible() const { return m_Visible; }
		inline void SetVisibility(bool visible) { m_Visible = visible; }

		inline void SetPosition(const Vector2& position) { m_Position = Vector3(position); }
		inline void SetSize(const Vector2& size) { m_Size = size; }
		inline void SetColor(uint color) { m_Color = color; }
		void SetColor(const Vector4& color);

		virtual void Submit(Renderer2D* renderer) const;

	public:
		static const std::vector<Vector2>& GetDefaultUVs();

	protected:
		Renderable2D();

	protected:
		Vector3 m_Position;
		Vector2 m_Size;
		uint m_Color;

		std::vector<Vector2> m_UVs;
		Texture* m_Texture;
		
		bool m_Visible;
	};

}