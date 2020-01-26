#include "pepch.h"
#include "DebugDraw.h"
#include "engine\Core\Scene2D.h"
#include "engine\Graphics\Cameras\EditorCamera.h"
#include "PhysicsContext.h"
#include <cstdio>
#include <cstdarg>
#include <cstring>



//#include <glad\glad.h>

namespace PrettyEngine {

	DebugDraw::DebugDraw()
	{
		//m_Scene = new Scene2D(new EditorCamera(Vector3(0.2f, 2.6f, 9.6f),Matrix4::Perspective(60.0f, 1280/720, 1.0f, 1000.0f)));
		m_Camera = new EditorCamera(Vector3(0.0f, 0.0f, -50.0f),Matrix4::Orthographic(-180.0f, 180.0f, -100.0f, 100.0f, -100.0f, 1000.0f));// Matrix4::Orthographic(-180.0f, 180.0f, -100.0f, 100.0f, -100.0f, 1000.0f));
		m_DebugRenderer = new Renderer2D(m_Camera);
	}

	DebugDraw::~DebugDraw()
	{
		//delete m_DebugRenderer;
	}


	void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {

		uint col = (uint)(color.a * 255.0f) << 24 | (uint)(color.b * 255.0f) << 16 | (uint)(color.g * 255.0f) << 8 | (uint)(color.r * 255.0f);
		b2Vec2 size = vertices[2] - vertices[0];
		//m_DebugRenderer->DrawRect(Vector2(vertices[0].x, vertices[0].y), Vector2(size.x, size.y), col, 0.5f);
		m_DebugRenderer->DrawLine(Vector2(vertices[0].x, vertices[0].y), Vector2(vertices[1].x, vertices[1].y), col, 0.5f);
		m_DebugRenderer->DrawLine(Vector2(vertices[1].x, vertices[1].y), Vector2(vertices[2].x, vertices[2].y), col, 0.5f);
		m_DebugRenderer->DrawLine(Vector2(vertices[2].x, vertices[2].y), Vector2(vertices[3].x, vertices[3].y), col, 0.5f);
		m_DebugRenderer->DrawLine(Vector2(vertices[3].x, vertices[3].y), Vector2(vertices[0].x, vertices[0].y), col, 0.5f);
	}

	void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {

		Vector4 col(color.r, color.g, color.b, color.a);
		b2Vec2 size = vertices[0] + vertices[2];
		//m_DebugRenderer->DrawRect(Vector2(vertices[0].x, vertices[0].y), Vector2(size.x, size.y),0xff0000ff, 2.0f);
	}

	void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {

	}

	void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {

	}

	void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		m_DebugRenderer->DrawLine(Vector2(p1.x, p1.y), Vector2(p2.x, p2.y), Vector4(color.r, color.g, color.b, color.a));
	}

	void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) {

	}

	void DebugDraw::DrawString(int x, int y, const char *string, ...) {
		// TODO:
	}

	void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& c) {

		uint col = (uint)(1 * 255.0f) << 24 | (uint)(c.b * 255.0f) << 16 | (uint)(c.g * 255.0f) << 8 | (uint)(c.r * 255.0f);
		b2Vec2 size = aabb->lowerBound + aabb->upperBound;
		//m_DebugRenderer->DrawRect(Vector2(aabb->lowerBound.x, aabb->lowerBound.y), Vector2(size.x, size.y), col, 1.f);
	}

	void DebugDraw::DrawTransform(const b2Transform& xf) {

		b2Vec2 p1 = xf.p, p2;
		const float32 k_axisScale = 0.4f;

		p2 = p1 + k_axisScale * xf.q.GetXAxis();
		DrawSegment(p1, p2, b2Color(1, 0, 0));

		p2 = p1 + k_axisScale * xf.q.GetYAxis();
		DrawSegment(p1, p2, b2Color(0, 1, 0));
	}
}

