#pragma once
#include "Component.h"
#include "engine\Maths\maths.h"

namespace PrettyEngine {

	class Rigidbody;

	class Transform : public Component
	{
		
	public:
		Vector3 position, rotation, scale; //EulerAngles rotation

	
	public:
		Transform();
		Transform(const Vector3& position);
		Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale);
		~Transform();

		inline Matrix4* ModelMatrix() { return m_ModelMatrix; }

		void Translate(const Vector3& step);
		void Update();

		virtual ComponentType GetType() const override { return GetStaticType(); }

		static ComponentType GetStaticType() {
			static ComponentType type = ComponentType::Transform;
			return type;
		}

		virtual void Init() override;

	private:
		Matrix4* m_ModelMatrix = new Matrix4(1.0f);
		Rigidbody* m_Rigidbody = nullptr;

		Matrix4 TranslateInternal();
		Matrix4 RotateInternal();
		Matrix4 ScaleInternal();

		inline void SetRigidbody(Rigidbody* rb) { m_Rigidbody = rb; }
		friend class Rigidbody;

	};
}
