#include "pepch.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "engine\Core\Application.h"

namespace PrettyEngine {

	Transform::Transform()
	{
		position = Vector3::Zero();
		rotation = Vector3::Zero();
		scale = Vector3(1.0f);
	
	}
	Transform::Transform(const Vector3& position)
		: position(position)
	{
		rotation = Vector3::Zero();
		scale = Vector3(1.0f);
	
	}
	Transform::Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale)
		: position(position), rotation(rotation), scale(scale)
	{
		
	}

	Transform::~Transform()
	{
		delete m_ModelMatrix;
	}

	void Transform::Translate(const Vector3 & step)
	{
		position += step;
	}

	void Transform::Update()
	{
		/*Rigidbody* rb = entity->GetComponent<Rigidbody>();
		if (rb) {
			position.x = rb->GetPosition().x;
			position.y = rb->GetPosition().y;
		}*/
		//m_Rigidbody = entity->GetComponent<Rigidbody>();
		if (m_Rigidbody != nullptr && !Application::Get().EditorInUse())
		{
			position.x = m_Rigidbody->GetPosition()->x;
			position.y = m_Rigidbody->GetPosition()->y;

		}

		*m_ModelMatrix = TranslateInternal() * RotateInternal() * ScaleInternal();
	}

	void Transform::Init()
	{
		//m_Rigidbody = entity->GetComponent<Rigidbody>();

	}

	Matrix4 Transform::TranslateInternal()
	{
		return Matrix4::Translate(position);
	}

	Matrix4 Transform::RotateInternal()
	{
		Matrix4 rotMatrix = Matrix4(1.0f);
		rotMatrix *= Matrix4::Rotate(rotation.x, Vector3::XAxis());
		rotMatrix *= Matrix4::Rotate(rotation.y, Vector3::YAxis());
		rotMatrix *= Matrix4::Rotate(rotation.z, Vector3::ZAxis());

		return rotMatrix;
	}

	Matrix4 Transform::ScaleInternal()
	{
		return Matrix4::Scale(scale);
	}
}