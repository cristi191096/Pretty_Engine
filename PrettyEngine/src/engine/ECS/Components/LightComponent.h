#pragma once

#include "Component.h"
#include "engine\Graphics\Light.h"

namespace PrettyEngine {

	class Transform;

	class LightComponent : public Component
	{

	public:
		Vector3 m_Diffuse, m_Ambient, m_Specular;
		float m_Radius = 2.0f;
		float m_Intensity = 1.0f;
		Light::Type m_Type;
		Light* light;		// TODO: Make light private


		LightComponent( Light::Type type, const Vector3& diffuse = Vector3(1.f, 1.f, 1.f), const Vector3& ambient = Vector3(0.2f, 0.2f, 0.2f), const Vector3& specular = Vector3(1.f, 1.f, 1.f), const float& intensity = 1.f, const float& radius = 2.f);
		~LightComponent();

		virtual ComponentType GetType() const override { return GetStaticType(); }

		static ComponentType GetStaticType() {
			static ComponentType type = ComponentType::Light;
			return type;
		}

		virtual void Init() override;


	private:
		Transform* m_Transform;
	};
}