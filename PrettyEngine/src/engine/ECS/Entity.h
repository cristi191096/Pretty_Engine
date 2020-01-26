#pragma once

namespace PrettyEngine {

	class Component;
	class EditorLayer;

	class Entity 
	{
	public:
		String tag;
		String name = "Entity";

	public:
		Entity(const String& entityName = "Entity", const String& entityTag = "Untaged");
		~Entity();

		//Template
		template <typename T>
		T* GetComponent()
		{
			for (uint i = 0; i < m_Components.size(); i++) {
				if (m_Components[i]->GetType() == T::GetStaticType())
					return (T*)m_Components[i];
			}

		//	PE_CORE_ERROR("Component unknown or couldn't be found!");
			return nullptr;
		}												// { return m_Components[type]; }	//TODO: Fix adding extra stuff. Use iterator.

		//template <>
		//Transform* GetComponent<Transform>()
		//{
		//	for (uint i = 0; i < m_Components.size(); i++)
		//	{
		//		if (static_cast<Transform*>(m_Components[i]))
		//		{
		//			return (Transform*)m_Components[i];
		//		}
		//	}
		//}
		//
		//template <>
		//LightComponent* GetComponent<LightComponent>()
		//{
		//	for (uint i = 0; i < m_Components.size(); i++)
		//	{
		//		if (static_cast<LightComponent*>(m_Components[i]))
		//		{
		//			return (LightComponent*)m_Components[i];
		//		}
		//	}
		//}
		//
		//template <>
		//ModelComponent* GetComponent<ModelComponent>()
		//{
		//	for (uint i = 0; i < m_Components.size(); i++)
		//	{
		//		if (dynamic_cast<ModelComponent*>(m_Components[i]))
		//		{
		//			return (ModelComponent*)m_Components[i];
		//		}
		//	}
		//}

		void AddComponent(Component* component);
		void RemoveComponent(Component * component);
	

	protected:
		//std::vector<Component*> m_Components;
		std::vector<Component*> m_Components;

	private:
		struct EditorProperties
		{
			// char name[40 + 1];
			//Transform
			float position[3] = { 0,0,0 };
			float rotation[3] = { 0,0,0 };
			float scale[3] = { 1,1,1 };
			//Mesh
			float shininess = 128.0f;
		
		};

		EditorProperties m_Properties;

		friend EditorLayer;
	};
}