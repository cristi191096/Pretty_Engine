#include "pepch.h"
#include "Entity.h"
//#include "Components\TransformComponent.h"
#include "Components\Components.h"
#include "editor\EditorLayer.h"


namespace PrettyEngine {

	Entity::Entity(const String& entityName, const String& entityTag)
		: tag(entityTag), name(entityName)
	{
	/*	memset(m_Properties.name, 0, 40 + 1);
		if (entityName.size() < 40)
		{
			for (int i = 0; i < entityName.size(); i++)
			{
				m_Properties.name[i] = entityName[i];
			}
			m_Properties.name[41] = '\0';
		}
		else
		{
			PE_ERROR("{0} Entity: Name is too long (max 40 characters) >> Used default name! ", entityName);
			m_Properties.name[0] = 'E';
			m_Properties.name[1] = 'n';
			m_Properties.name[2] = 't';
			m_Properties.name[3] = 'i';
			m_Properties.name[4] = 't';
			m_Properties.name[5] = 'y';
			m_Properties.name[6] = '\0';
		
		}*/
		AddComponent(new Transform());
	}

	Entity::~Entity()
	{
		for (uint i = 0; i < m_Components.size(); i++)
		{
			delete m_Components[i];
		}

		m_Components.clear();
	}

	void Entity::AddComponent(Component * component)
	{
		if (component == nullptr || component->GetType() == ComponentType::Null)
		{
			PE_CORE_ERROR("Component does not exist: Type is NULL!");
			return;
		}
		for (uint i = 0; i < m_Components.size();i++)
		{
			if (component->GetType() == m_Components[i]->GetType()) 
			{
				PE_CORE_ERROR("Component already exists in this entity!");
				return;
			}
		}

		switch (component->GetType())
		{
		case ComponentType::Transform:
		{
			Transform* tr = (Transform*)component;
			m_Properties.position[0] = tr->position.x;
			m_Properties.position[1] = tr->position.y;
			m_Properties.position[2] = tr->position.z;

			m_Properties.rotation[0] = tr->rotation.x;
			m_Properties.rotation[1] = tr->rotation.y;
			m_Properties.rotation[2] = tr->rotation.z;

			m_Properties.scale[0] = tr->scale.x;
			m_Properties.scale[1] = tr->scale.y;
			m_Properties.scale[2] = tr->scale.z;
		}
		default:
			break;
		}

		/*m_Components[component->GetType()] = component;*/
		component->entity = this;
		component->Init();
		m_Components.push_back(component);
	}

	void Entity::RemoveComponent(Component * component)
	{
		auto it = std::find(m_Components.begin(), m_Components.end(), component);
		if (it != m_Components.end()) 
		{
			m_Components.erase(it);
		}
	}

}