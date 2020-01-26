#include "pepch.h"
#include "Body.h"
#include "engine\ECS\Components\TransformComponent.h"

namespace PrettyEngine {

	static b2BodyType BodyTypeToBox2D(BodyType type) 
	{
		switch (type)
		{
		case BodyType::STATIC:			return b2_staticBody;
		case BodyType::KINEMATIC:		return b2_kinematicBody;
		case BodyType::DYNAMIC:			return b2_dynamicBody;
		}
	}

	static BodyType Box2DToBodyType(b2BodyType type) 
	{
		switch (type)
		{
		case b2_staticBody:		return BodyType::STATIC;
		case b2_kinematicBody:	return BodyType::KINEMATIC;
		case b2_dynamicBody:	return BodyType::DYNAMIC;
		}
	}

	Body::Body()
	{
		
	}

	Body::~Body()
	{
		PhysicsContext::Get()->m_World->DestroyBody(m_Body);
	}

	void Body::Init( Vector3 & position, const Vector3 & size, BodyType type)
	{
		//TODO: The shape is not quite right for this overload. Should be tested
		m_Type = type;
		b2BodyDef bodyDef;
		bodyDef.type = BodyTypeToBox2D(type);
		bodyDef.position.Set(position.x, position.y);
		m_Body = PhysicsContext::Get()->m_World->CreateBody(&bodyDef);

		//m_Mass = m_Body->GetMass();

		b2PolygonShape shape;
		shape.SetAsBox(size.x / 2.0f, size.y / 2.0f);		//Should be Half of the size

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;		// Default density. Can be changed with SetDensity.
		fixtureDef.friction = 0.3f;		// Default friction. Can be changed with SetFriction.

		m_Fixture = m_Body->CreateFixture(&fixtureDef);


		ComputeMassData();
		
		/*position.x = m_Body->GetPosition().x;
		position.y = m_Body->GetPosition().y;*/
	}

	void Body::Init(Transform * transform, const float& density, const float& friction, const Vector2& minBound, const Vector2& maxBound, BodyType type)		// TODO: Should not depend on the trnsform.
	{
		m_Type = type;
		b2BodyDef bodyDef;
		bodyDef.type = BodyTypeToBox2D(type);
		bodyDef.position.Set(transform->position.x, transform->position.y);
		m_Body = PhysicsContext::Get()->m_World->CreateBody(&bodyDef);

		//m_Mass = m_Body->GetMass();

		b2PolygonShape shape;
		//shape.SetAsBox(transform->position.x / 2.0f, transform->position.y / 2.0f);		//Should be Half of the size
		b2Vec2 verts[4];
		verts[0] = b2Vec2((minBound.x) * transform->scale.x, (minBound.y) * transform->scale.y);
		verts[1] = b2Vec2((maxBound.x) * transform->scale.x, (minBound.y) * transform->scale.y);
		verts[2] = b2Vec2((maxBound.x) * transform->scale.x, (maxBound.y) * transform->scale.y);
		verts[3] = b2Vec2((minBound.x) * transform->scale.x, (maxBound.y) * transform->scale.y);

		shape.Set(&verts[0], 4);
		//shape.SetAsBox(10, 10, b2Vec2(transform->position.x, transform->position.y), 0);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = density;		// Default density. Can be changed with SetDensity.
		fixtureDef.friction = friction;		// Default friction. Can be changed with SetFriction.

		m_Fixture = m_Body->CreateFixture(&fixtureDef);

		
		ComputeMassData();

		// m_Body->SetFixedRotation(true);
		
		//*transform->position = GetPosition();

	}

	void Body::SetShape(Transform* transform, const float& density, const float& friction, const Vector2& minBound, const Vector2& maxBound) 
	{
		m_Body->DestroyFixture(m_Fixture);
		b2PolygonShape shape;
		b2Vec2 verts[4];
		verts[0] = b2Vec2((minBound.x) * transform->scale.x, (minBound.y) * transform->scale.y);
		verts[1] = b2Vec2((maxBound.x) * transform->scale.x, (minBound.y) * transform->scale.y);
		verts[2] = b2Vec2((maxBound.x) * transform->scale.x, (maxBound.y) * transform->scale.y);
		verts[3] = b2Vec2((minBound.x) * transform->scale.x, (maxBound.y) * transform->scale.y);

		shape.Set(&verts[0], 4);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = density;		
		fixtureDef.friction = friction;		

		m_Fixture = m_Body->CreateFixture(&fixtureDef);
	}

	void Body::ApplyForce(const Vector2 & force, Vector2* point, bool wake)
	{
		//Vector2* vec = &GetPosition();
		 m_Body->ApplyForce(b2Vec2(force.x, force.y), b2Vec2(point->x, point->y) , wake);
	//	m_Body->SetLinearVelocity(b2Vec2(-10, 0.0f));
		
		 //PE_CORE_TRACE( m_Body->GetLinearVelocity()
		
	}

	void Body::ApplyForce(const Vector2 & force)
	{
		m_Body->ApplyForce(b2Vec2(force.x, force.y), m_Body->GetPosition(), true);
	}

	void Body::ComputeMassData()
	{
		b2MassData mass;
		m_Fixture->GetShape()->ComputeMass(&mass, m_Fixture->GetDensity());
		m_MassData.mass = mass.mass;
		m_MassData.centroid = Vector2(mass.center.x, mass.center.y);
		m_MassData.inertia = mass.I;
	}

}