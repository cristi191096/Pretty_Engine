#include "pepch.h"
#include "Camera.h"

namespace PrettyEngine {

	Camera::Camera(const Matrix4& projectionMatrix)
		: m_ProjectionMatrix(projectionMatrix)
	{
		m_ViewMatrix = Matrix4::Identity();
		m_Position = Vector3();
		m_Rotation = Vector3();
	}

	Camera::~Camera()
	{
	}
	Vector3 Camera::GetUpDirection()
	{
		return Quaternion::Rotate(GetOrientation(), Vector3::YAxis());
	}
	Vector3 Camera::GetRightDirection()
	{
		return Quaternion::Rotate(GetOrientation(), Vector3::XAxis());
	}
	Vector3 Camera::GetForwardDirection()
	{
		return Quaternion::Rotate(GetOrientation(), -Vector3::ZAxis());
	}
	Quaternion Camera::GetOrientation()
	{
		return Quaternion::RotationY(-m_Yaw) * Quaternion::RotationX(-m_Pitch);
	}
}