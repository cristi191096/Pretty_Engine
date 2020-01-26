#pragma once
#include "engine\Maths\Vector3.h"

namespace PrettyEngine {

	class Shader;

	class Light {

	public:
		enum Type {
			DIRECTIONAL = 0, POINT, SPOT
		};

		Vector3 m_Diffuse, m_Ambient, m_Specular, m_Position, m_Direction;
		float m_Radius = 2.0f;
		float m_Intensity = 1.0f;
		Type m_Type;		// Allow to change the type so this changes the way the light is behaving.

		Light(Type type, const Vector3& direction, const Vector3& diffuse, const Vector3& ambient, const Vector3& specular);			// Constructor for Directional light
		Light(Type type, const Vector3& position, const Vector3& diffuse, const Vector3& ambient, const Vector3& specular, const float& radius, const float& intensity);			// Constructor for Point light
		~Light();

		void UpdateAttenuation();
		void SetUniforms(Shader* shader);

	private:
		float Kc = 1.0f;
		float Kl = 0.09f;
		float Kq = 0.032f;
	};
}
