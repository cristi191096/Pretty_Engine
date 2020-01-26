#include "pepch.h"
#include "Material.h"


namespace PrettyEngine {

	Material::Material(Shader * shader)
		: m_Shader(shader)
	{
	}

	Material::Material(const std::vector<Texture2D*>& textures, Shader* shader)
		: m_Textures(textures), m_Shader(shader)
	{
	}

	Material::~Material()
	{
		for (Texture2D* texture : m_Textures)
		{
			if (texture) //0xFFFFFFFFFFFFFFFF
			{
			//	delete texture;	//TODO: Fix this
			}
		}
		m_Textures.clear();
	}

	void Material::Bind()
	{
		// bind appropriate textures

		m_Shader->Bind();

		if (m_Shader->GetType() == Shader::Type::FLAT) 
		{
			m_Shader->SetUniform3f("u_Material.diffuseColour", m_DiffuseColour);

			for (uint i = 0; i < m_Textures.size(); i++)
			{

				m_Textures[i]->Bind(i);
				switch (m_Textures[i]->GetParameters().type)
				{
				case TextureType::Diffuse:
					m_Shader->SetUniform1i("u_Material.diffuseMap", i);
					break;
				}

			}
		}
		else if (m_Shader->GetType() == Shader::Type::BLINPHONG) 
		{
			m_Shader->SetUniform3f("u_Material.diffuseColour", m_DiffuseColour);
			m_Shader->SetUniform3f("u_Material.specularColour", m_SpecularColour);
			m_Shader->SetUniform3f("u_Material.emissionColour", m_EmissionColour);
			m_Shader->SetUniform1f("u_Material.shininess", m_Shininess);


			for (uint i = 0; i < m_Textures.size(); i++)
			{
				

				m_Textures[i]->Bind(i);
				switch (m_Textures[i]->GetParameters().type)
				{
				case TextureType::Diffuse:
					m_Shader->SetUniform1i("u_Material.diffuseMap", i);
					break;
				case TextureType::Specular:
					m_Shader->SetUniform1i("u_Material.specularMap", i);
					break;
				case TextureType::Height:
					m_Shader->SetUniform1i("u_Material.bumpMap", i);		// Assimp returns the bumpMap as Height map
					break;
					//case TextureType::Height:
					//	m_Shader->SetUniform1i("u_Material.diffuseMap", i);
					//	break;

				default:
					PE_CORE_WARN("Texture type not processed!");
					break;
				}

			}
		}
		else
		{
			PE_CORE_ERROR("Unable to bind the textures! Please check the Shader's Uniforms! Shader Name: {0}", m_Shader->GetName());
		}

		//TODO: Set Uniforms
	}

		

	void Material::Unbind()
	{
		m_Shader->Unbind();

		for (uint i = 0; i < m_Textures.size(); i++)
		{
			Texture* texture = m_Textures[i];
			if (texture)
				texture->Unbind(i);
		}
	}
}