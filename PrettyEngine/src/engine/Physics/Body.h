#pragma once
#include "PhysicsContext.h"
#include "engine\Maths\Vector2.h"

namespace PrettyEngine {

	enum BodyType {
		STATIC = 0,
		KINEMATIC,
		DYNAMIC
	};

	class Transform;

	class Body {

	public:
		Body();
		~Body();

		void Init(Vector3& position, const Vector3& size, BodyType type);
		void Init(Transform* transform, const float& density, const float& friction, const Vector2& minBound, const Vector2& maxBound, BodyType type);

		inline void UseGravity(bool use) { m_Body->SetGravityScale(use ? 1 : 0); }
		inline void SetDensity(const float& density) { if (density <= 0) PE_CORE_WARN("Dynamic objects can't have 0 density!"); m_Fixture->SetDensity(density); }
		inline const float& GetDensity() const { return m_Fixture->GetDensity(); }

		inline void SetFriction(const float& friction) { m_Fixture->SetFriction(friction); }
		inline const float& GetFriction() const { return m_Fixture->GetFriction(); }

		inline const float& GetMass() const { return m_MassData.mass; }
		inline const float& GetInertia() const { return m_MassData.inertia; }
		inline const Vector2& GetCentreOfMass() const { return m_MassData.centroid; }

		inline Vector2& GetPosition() const { return Vector2(m_Body->GetPosition().x, m_Body->GetPosition().y); }
		inline Vector2& GetVelocity() const { return Vector2(m_Body->GetLinearVelocity().x, m_Body->GetLinearVelocity().y); }

		void ApplyForce(const Vector2& force, Vector2* point, bool wake);
		void ApplyForce(const Vector2& force);
		inline void SetLinearVelocity(const Vector2& velocity) {m_Body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y)); }// m_Body->SetAngularVelocity(10); }//

		void SetShape(Transform* transform, const float& density, const float& friction, const Vector2& minBound, const Vector2& maxBound);

	private:
		struct MassData {
			float mass;
			Vector2 centroid;
			float inertia;
		};

		MassData m_MassData;
		b2Body* m_Body = nullptr;
		b2Fixture* m_Fixture = nullptr;
		BodyType m_Type;

	private:
		void ComputeMassData();
	};
}
