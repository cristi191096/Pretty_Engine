#include "pepch.h"
#include "Light.h"
#include "engine\Graphics\Shaders\Shader.h"

namespace PrettyEngine {
	Light::Light(Type type, const Vector3 & direction, const Vector3 & diffuse, const Vector3 & ambient, const Vector3 & specular)
		: m_Type(type), m_Diffuse(diffuse), m_Ambient(ambient), m_Specular(specular)
	{
		m_Direction = direction.Normalise();		// Make sure the light direction is normalised. 
	}

	Light::Light(Type type, const Vector3 & position, const Vector3 & diffuse, const Vector3 & ambient, const Vector3 & specular, const float & radius, const float & intensity)
		: m_Type(type), m_Position(position), m_Diffuse(diffuse), m_Ambient(ambient), m_Specular(specular), m_Radius(radius), m_Intensity(intensity)
	{
		Kl = 2 / m_Radius;
		Kq = 1 / (m_Radius * m_Radius);
	}

	Light::~Light()
	{
	}

	void Light::UpdateAttenuation()
	{
		Kl = 2 / m_Radius;
		Kq = 1 / (m_Radius * m_Radius);
	}

	void Light::SetUniforms(Shader * shader)
	{
		//Assume that the shader is already bound

		if (m_Type == Type::DIRECTIONAL) 
		{
			//there is only one directional light in the scene
			// If there are more, the last one is going to override the others.
			//m_Direction.x += 0.001f;
			//m_Direction.z += 0.01f;//= Vector3(0, 0, 0);
			//m_Direction = m_Direction.Normalise();
			
			shader->SetUniform3f("u_DirectionalLight.direction", m_Direction);
			shader->SetUniform3f("u_DirectionalLight.ambient", m_Ambient);
			shader->SetUniform3f("u_DirectionalLight.diffuse", m_Diffuse);
			shader->SetUniform3f("u_DirectionalLight.specular", m_Specular);
		}
		else if (m_Type == Type::POINT) 
		{
			// TODO: Set the uniforms
			shader->SetUniform3f("u_PointLight.position", m_Position);
			shader->SetUniform3f("u_PointLight.ambient", m_Ambient);
			shader->SetUniform3f("u_PointLight.diffuse", m_Diffuse);
			shader->SetUniform3f("u_PointLight.specular", m_Specular);
			shader->SetUniform1f("u_PointLight.intensity", m_Intensity);
			shader->SetUniform1f("u_PointLight.constant", Kc);
			shader->SetUniform1f("u_PointLight.linear", Kl);
			shader->SetUniform1f("u_PointLight.quadratic", Kq);
		}

		PE_CORE_ASSERT(m_Type != Type::SPOT, "Not Implemented yet!" )	// It is not important for the game 
	}


}