#pragma once
#include "Types.h"
#include "engine\ECS\Entity.h"

namespace PrettyEngine {

//	/* Identifier for component. Used for Data Driven level building*/
//	struct ComponentType {
//		String name = "NULL";
//	};
	enum class ComponentType
	{
		Null = 0,
		Transform, Model, Light, Rigidbody, Audio
	};
	
	//Virtual interface for all components
	class Component {

	public:
		Component() {}
		virtual ~Component() {}
		virtual ComponentType GetType() const { return ComponentType::Null; }

	protected:
		virtual void Init() = 0;

	protected:
		// Tell the component what entity belongs to. Needed as most of the components should know about the others (e.g. Rigidbody and Light should know the position of the entity)
		Entity* entity;	
		friend Entity;

	};
}