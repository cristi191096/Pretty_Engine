#pragma once

#include "Component.h"
#include "engine\Physics\Body.h"

namespace PrettyEngine {

	class Transform;
	class ModelComponent;

	class Rigidbody : public Component
	{

	public:
		// TODO: Find a way to update the body properties with these variables.
		//bool m_canJump = true; // Determines if the entity has touched the ground
		
		float m_Mass;
		float m_Density;
		float m_Drag;			//Friction
		

	public:
		
	
		Rigidbody(const float& density, const float& drag ,BodyType type = BodyType::DYNAMIC);
		~Rigidbody();

		virtual ComponentType GetType() const override { return GetStaticType(); }

		static ComponentType GetStaticType() {
			static ComponentType type = ComponentType::Rigidbody;
			return type;
		}

		virtual void Init() override;

		inline BodyType GetBodyType() const { return m_Type; }
		inline void SetBodyType(BodyType type) { m_Type = type; }
		inline Vector2* GetPosition() const { return &m_Body.GetPosition(); }
		inline Vector2* GetVelocity() const { return &m_Body.GetVelocity(); }
		inline void ApplyForce(const Vector2& force, Vector2* point, bool wake) { m_Body.ApplyForce(force, point, wake); }
		inline void ApplyForce(const Vector2 & force) { m_Body.ApplyForce(force); }
		inline void SetLinearVeclocity(const Vector2& velocity) { m_Body.SetLinearVelocity(velocity); }
		inline void UseGravity(bool use) { m_Body.UseGravity(use); }

		inline void SetDensity() { m_Body.SetDensity(m_Density); }
		inline void SetDrag() { m_Body.SetFriction(m_Drag); }
		inline void SetCollider(const Vector2& minBound, const Vector2& maxBound) { m_Body.SetShape(m_Transform, m_Density, m_Drag, minBound, maxBound); }

	private:
		Body m_Body;
		BodyType m_Type;
		Transform* m_Transform;
		ModelComponent* m_ModelComp;

	};
}