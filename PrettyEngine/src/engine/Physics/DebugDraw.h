#pragma once
#include <Box2D\Box2D.h>
#include "engine\Graphics\Renderer2D.h"
#include "engine\Graphics\Cameras\Camera.h"



namespace PrettyEngine {

	class DebugDraw : public b2Draw
	{
	public:
		DebugDraw();
		~DebugDraw();

		void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

		void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

		void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

		void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

		void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

		void DrawTransform(const b2Transform& xf);

		void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);

		void DrawString(int x, int y, const char* string, ...);

		void DrawAABB(b2AABB* aabb, const b2Color& color);


		Renderer2D* m_DebugRenderer;
		Camera* m_Camera;


	};

}