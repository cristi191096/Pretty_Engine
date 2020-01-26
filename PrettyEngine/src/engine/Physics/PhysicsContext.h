#pragma once
#include "engine\Core\Core.h"

#include <Box2D\Box2D.h>

#ifdef PE_DEBUG
#include "DebugDraw.h"
#endif // PE_DEBUG


namespace PrettyEngine {

	/*
		Singleton for Physics subsystem. Manages initialisation, updates and events for physics entities. 
	*/

	class PE_API PhysicsContext {

	

	public:
		// Gravity is already negative, so + goes down and - goes up
		static void Create(const float& gravity = 9.81f);

		inline static PhysicsContext* Get() { return s_Context; }

		void Update();

		void Destroy() const;

	private:
		static PhysicsContext* s_Context;
		PhysicsContext(const float& gravityAmplifier);
		~PhysicsContext();

	private:
		std::unique_ptr<b2World> m_World;
#ifdef PE_DEBUG
		DebugDraw* fooDrawInstance = nullptr;
#endif // PE_DEBUG

		friend class Body;
		friend class DebugDraw;

	};
}