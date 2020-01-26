#include "pepch.h"
#include "PhysicsContext.h"
#include "DebugDraw.h"
#include "Body.h"


namespace PrettyEngine {

	PhysicsContext* PhysicsContext::s_Context = nullptr;

	PhysicsContext::PhysicsContext(const float& gravityAmplifier)
	{
		b2Vec2 gravity(0, -gravityAmplifier);
		m_World = std::make_unique<b2World>(gravity);

		//Ground
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0, -80);
		b2Body* groundBody = m_World->CreateBody(&groundBodyDef);

		b2PolygonShape groundBox;
		groundBox.SetAsBox(5000.0f, 0.0f);
		groundBody->CreateFixture(&groundBox, 0.0f);

		 // setup debugDraw
#ifdef PE_DEBUG
		fooDrawInstance = new DebugDraw();
		m_World->SetDebugDraw(fooDrawInstance);
		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		flags += b2Draw::e_aabbBit;
		flags += b2Draw::e_pairBit;
		flags += b2Draw::e_centerOfMassBit;
		fooDrawInstance->SetFlags(flags);

	//	glMatrixMode(GL_PROJECTION);
	//	gluPerspective(60, 1, 0.2f, 200);
	//	glLoadIdentity();
#endif
	}

	PhysicsContext::~PhysicsContext()
	{
	}

	void PhysicsContext::Create(const float& gravity)
	{
		s_Context = new PhysicsContext(gravity);
	}

	void PhysicsContext::Update()
	{
		//m_World->Step(1.0f / 60.0f, 6, 2);
		//m_World->ClearForces();
#ifdef PE_DEBUG
	
		m_World->Step(1.0f / 60.0f, 8, 3);	// TODO: Hardcoded values. Set the timeStep from the engine.
		m_World->ClearForces();
		fooDrawInstance->m_DebugRenderer->Begin();
		m_World->DrawDebugData();
		fooDrawInstance->m_DebugRenderer->End();
		fooDrawInstance->m_Camera->Update();
		fooDrawInstance->m_DebugRenderer->Flush();
		// glColor4f(1,1,1,1);
  //  glBegin(GL_LINES);
  //  
  //      glVertex2f(0, 0);
		//glVertex2f(10, 10);
  //  
  //  glEnd();

		//glFlush();
#else
		m_World->Step(1.0f / 60.0f, 6, 2);
		m_World->ClearForces();
#endif
	}

	void PhysicsContext::Destroy() const
	{
	}


}