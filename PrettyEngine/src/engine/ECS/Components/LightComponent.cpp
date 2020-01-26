#include "pepch.h"
#include "LightComponent.h"
#include "TransformComponent.h"

PrettyEngine::LightComponent::LightComponent(Light::Type type, const Vector3 & diffuse, const Vector3 & ambient, const Vector3 & specular, const float & intensity, const float & radius)
	: m_Type(type), m_Diffuse(diffuse), m_Ambient(ambient), m_Specular(specular), m_Intensity(intensity), m_Radius(radius)
{


}

PrettyEngine::LightComponent::~LightComponent()
{
	delete light;
}

void PrettyEngine::LightComponent::Init()
{
	m_Transform = entity->GetComponent<Transform>();
	PE_CORE_ASSERT(m_Transform, "Transform couldn't be found. Returned NULL!");	

	//Quaternion orientation = Quaternion::FromEulerAngles(m_Transform->rotation);
	//Vector3 direction = Vector3(2 * (orientation.x * orientation.z + orientation.w * orientation.y),
	//							2 * (orientation.y * orientation.z - orientation.w * orientation.x),
	//						1 - 2 * (orientation.x * orientation.x + orientation.y * orientation.y));	// Forward vector
	switch (m_Type)
	{
	case PrettyEngine::Light::DIRECTIONAL:
		light = new Light(m_Type, m_Transform->rotation, m_Diffuse, m_Ambient, m_Specular);		// Send the position only and find the direction based on that. Or just give it some values in the level xml.
		break;
	case PrettyEngine::Light::POINT:
		light = new Light(m_Type, m_Transform->position, m_Diffuse, m_Ambient, m_Specular, m_Intensity, m_Radius);
		break;
	case PrettyEngine::Light::SPOT:
		break;
	default:
		break;
	}
}
