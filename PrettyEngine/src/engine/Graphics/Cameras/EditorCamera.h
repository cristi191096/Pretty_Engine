#pragma once
#include "Camera.h"
#include "engine\Events\MouseEvent.h"

namespace PrettyEngine {

	class EditorCamera : public Camera
	{
	public:
		EditorCamera(const Vector3& position, const Matrix4& projectionMatrix);
		EditorCamera(const Matrix4& projectionMatrix);
		~EditorCamera();

		void Focus() override;
		void Update() override;
		virtual void OnEvent(Event& ev) override;

		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(float distance) { m_Distance = distance; }

	private:
		Vector2 m_InitialMousePosition;
		bool m_Panning, m_Rotating;
		float m_Distance;
		float m_PanSpeed, m_RotationSpeed, m_ZoomSpeed;
	private:
		Vector3 CalculatePosition();

		void MousePan(const Vector2& delta);	// Takes in the delta between Mouse Position and Initial Mouse Position
		void MouseRotate(const Vector2& delta);	// Takes in the delta between Mouse Position and Initial Mouse Position
		void MouseZoom(float delta);

		bool OnScroll(MouseScrolledEvent& ev);

	};

}