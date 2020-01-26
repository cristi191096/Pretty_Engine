#pragma once
#include "engine\Core\Core.h"
#include "engine\Graphics\Shaders\Shader.h"
#include "engine\Graphics\Shaders\ShaderLibrary.h"
#include "engine\Graphics\Texture2D.h"

namespace PrettyEngine {

	class PE_API Material {

	public:
		Material(Shader* shader = blinPhongShader());
		Material(const std::vector<Texture2D*>& textures, Shader* shader = blinPhongShader());
		~Material();

		void Bind();
		void Unbind();

		
		inline void SetShader(Shader* shader) { m_Shader = shader; }
		inline void SetTextures(const std::vector<Texture2D*>& textures) { m_Textures = textures; }
		inline const std::vector<Texture2D*>& GetTextures() const { return m_Textures; }
		inline void SetDiffuseColour(const Vector3& col) { m_DiffuseColour = col; }
		inline void SetSpecularColour(const Vector3& col) { m_SpecularColour = col; }
		inline void SetEmissionColour(const Vector3& col) { m_EmissionColour = col; }
		inline void SetShininess(const float& val) { m_Shininess = val; }

		inline Shader* GetShader() const { return m_Shader; }
		inline const Vector3& GetDiffuseColour() const { return m_DiffuseColour; }
		inline const Vector3& GetSpecularColour() const { return m_SpecularColour; }
		inline const Vector3& GetEmissionColour() const { return m_EmissionColour; }
		inline const float& GetShininess() const { return m_Shininess; }

	private:
		Shader* m_Shader;
		std::vector<Texture2D*> m_Textures;
		Vector3 m_DiffuseColour = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 m_SpecularColour = Vector3(1.0f, 1.0f, 1.0f);
		Vector3 m_EmissionColour = Vector3(0.0f, 0.0f, 0.0f);
		float m_Shininess = 128.0f;



	};
}