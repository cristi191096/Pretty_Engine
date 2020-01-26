#pragma once
#include "engine\Core\Core.h"
#include "engine\Maths\maths.h"

namespace PrettyEngine {

	class Event;

	class PE_API Camera
	{
	public:
		Camera(const Matrix4& projectionMatrix);
		virtual ~Camera();

		virtual void Focus() { }
		virtual void Update() { }
		virtual void OnEvent(Event& ev) = 0;

		virtual Vector3 GetUpDirection();
		virtual Vector3 GetRightDirection();
		virtual Vector3 GetForwardDirection();
		virtual Quaternion GetOrientation();

		inline const Vector3& GetPosition() const { return m_Position; }
		inline void SetPosition(const Vector3& position) { m_Position = position; }

		inline const Vector3& GetRotation() const { return m_Rotation; }
		inline void SetRotation(const Vector3& rotation) { m_Rotation = rotation; }

		inline const Matrix4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline void SetProjectionMatrix(const Matrix4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }

		inline void Translate(const Vector3& translation) { m_Position += translation; }
		inline void Rotate(const Vector3& rotation) { m_Rotation += rotation; }

		inline void Translate(float x, float y, float z) { m_Position += Vector3(x, y, z); }
		inline void Rotate(float x, float y, float z) { m_Rotation += Vector3(x, y, z); }

		inline const Vector3& GetFocalPoint() const { return m_FocalPoint; }

		inline const Matrix4& GetViewMatrix() const { return m_ViewMatrix; }


	protected:
		Matrix4 m_ProjectionMatrix, m_ViewMatrix;
		Vector3 m_Position, m_Rotation, m_FocalPoint;
		float m_Yaw, m_Pitch;		//In Radians
	};

	
}