#include "pepch.h"
#include "ShaderLibrary.h"
#include "ShaderManager.h"

namespace PrettyEngine {

	static const String defaultShader2DSource = 
		"#shader vertex														\n"
"#version 330 core															\n"
"layout (location = 0) in vec3 position;									\n"
"layout (location = 1) in vec2 uv;											\n"
"layout (location = 2) in float tid;										\n"
"layout (location = 3) in vec4 color;										\n"
""
"uniform mat4 u_ProjectionMatrix;											\n"
"uniform mat4 u_ViewMatrix;									\n"
""
"out vec4 pos;																\n"
"out vec4 col;																\n"
"out vec2 tex_uv;															\n"
"out float tex_id;															\n"
"void main()																\n"
"{																			\n"
"	gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(position, 1.0);				\n"
"	pos = vec4(position, 1);												\n"
"	col = color;															\n"
"	tex_uv = uv;															\n"
"	tex_id = tid;															\n"
"};																			\n"
"#shader fragment															\n"
"#version 330 core															\n"
"out vec4 color;															\n"
"in vec4 pos;																\n"
"in vec4 col;																\n"
"in vec2 tex_uv;															\n"
"in float tex_id;															\n"
"uniform sampler2D textures[32];											\n"
"void main()																\n"
"{																			\n"
"	vec4 texColor = col;													\n"
"	if (tex_id > 0.0)														\n"
"	{																		\n"
"		int texid = int(tex_id - 0.5);										\n"
"		texColor = col * texture(textures[texid], tex_uv);					\n" 
"	}																		\n"
"	color = texColor;														\n"
"};																			\n";	
	/* The layout should be the same for every 3D shader as this is the structure of a Vertex
		TODO: I could either construct the Vertex based on the shader layout or make a callback within the shader to allow customisation
		e.g. string shaderSource1 = "#version 330 ... void customfunction( _args_ ) { ";
			string customShader = " Some user defined shader calculations that goes inside customfunction()";
			string shaderSource2 = "void main() { customfunction(); gl_Position = pos; } 
			string finalShaderSource = shaderSource1 + customShader + shaderSource2; */
	static const String flatColourShaderSource =
		
		R"(
#shader vertex
#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;	
layout (location = 3) in vec3 bitangent;
layout (location = 4) in vec3 tangent;

uniform mat4 u_ProjectionMatrix;	
uniform mat4 u_ViewMatrix;	
uniform mat4 u_ModelMatrix;
																														
out vec2 texCoord;
								
void main()																
{																			
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(position, 1.0);	
	texCoord = uv;

															
};	

#shader fragment												
#version 330 core												
out vec4 color;	

in vec2 texCoord;

struct Material
{
	sampler2D diffuseMap;
	vec3 diffuseColour;		
																							
};

uniform Material u_Material;
				
void main()													
{																
														
	color = vec4( texture(u_Material.diffuseMap, texCoord).rgb * u_Material.diffuseColour, 1.0f);
};																																		
		
)";

	static const String blinPhongShaderSource = /* Just Phong yet! */
		
		R"(
#shader vertex
#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;	
layout (location = 3) in vec3 bitangent;
layout (location = 4) in vec3 tangent;

uniform mat4 u_ProjectionMatrix;	
uniform mat4 u_ViewMatrix;	
uniform mat4 u_ModelMatrix;

mat3 TBN;
mat3 normalMat;
																														
out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;
out mat3 TangentSpace;
								
void main()																
{	
	FragPos = vec3(u_ModelMatrix * vec4(position, 1.0));
    TexCoords = uv;    
	normalMat = transpose(inverse(mat3(u_ModelMatrix)));
	Normal = normalMat * normal;
	
	vec3 T = normalize(normalMat * tangent);
	vec3 N = normalize(normalMat * normal);
	vec3 B = normalize(normalMat * bitangent);
	T = normalize(T - dot(T, N) * N); //Gram-Schmidt (reorganise vectors to be perpendicular to each other again.)
	
	
	TBN = transpose(mat3(
	T.x, B.x, N.x, 
	T.y, B.y, N.y, 
	T.z, B.z, N.z ));
	

	TangentSpace = TBN;
																		
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(position, 1.0);	
															
};	

#shader fragment												
#version 330 core	
											
out vec4 FragColor;	

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;
in mat3 TangentSpace;

struct Material
{
	sampler2D diffuseMap;
	sampler2D specularMap;
	sampler2D bumpMap;
	sampler2D emissionMap;
	vec3 diffuseColour;	
	vec3 specularColour;	
	vec3 emissionColour;
	float shininess;																
};

//Lights
struct DirectionalLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float intensity;

	float constant;
    float linear;
    float quadratic;
};


uniform Material u_Material;
uniform DirectionalLight u_DirectionalLight;
uniform PointLight u_PointLight;
uniform vec3 u_CameraPosition;

DirectionalLight someLight;


				
//Prototypes
vec3 CalculateDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, float cutoff);

void main()													
{																
	someLight.direction = vec3(-1.0, -1.0, 0.0);
	someLight.ambient = vec3(0.3, 0.3, 0.3);;
	someLight.diffuse = vec3(1.0, 1.0, 1.0);;
	someLight.specular = vec3(1.0, 1.0, 1.0);;
	
	vec3 norm = (255.0/128.0 * texture(u_Material.bumpMap, TexCoords).rgb - 1.0) * (2.0 * Normal - 1.0); //in tangent space (-1, 1).
	norm = normalize(norm);

	vec3 viewDir = normalize(TangentSpace * u_CameraPosition - TangentSpace * FragPos);

	vec3 result = CalculateDirLight(u_DirectionalLight, norm, viewDir);

	result += CalculatePointLight(u_PointLight, norm, FragPos, viewDir, 0.3);	


	//for(int i=0; i<NUM_LIGHTS; i++)
	//{
	//		result += CalculatePointLight(pointLight[i], norm, FragPos, viewDir, 0.3);	
	//
	//}
	//
	vec3 emission = vec3(0.0);
	
	emission = texture(u_Material.emissionMap, TexCoords).rgb * u_Material.emissionColour;// * u_Material.emissionAmp;	//emissionAmp is 0 if the texture exists and 1 otherwise
	
	
	
	result += emission;

    FragColor = vec4(result , 1.0);

};		


vec3 CalculateDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(TangentSpace * (-light.direction));
	//ambient
	vec3 ambient = light.ambient * vec3(texture(u_Material.diffuseMap, TexCoords)) * u_Material.diffuseColour;
	//diffuse
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuseMap, TexCoords)) * u_Material.diffuseColour;

	//Specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(u_Material.specularMap, TexCoords)) * u_Material.specularColour;
	
	return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, float cutoff)
{
	vec3 lightDir = normalize(TangentSpace * light.position - fragPos);
	//ambient
	vec3 ambient = light.ambient * vec3(texture(u_Material.diffuseMap, TexCoords)) * u_Material.diffuseColour;
	//diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuseMap, TexCoords)) * u_Material.diffuseColour;
	//specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(u_Material.specularMap, TexCoords)) * u_Material.specularColour;

	//Attenuation
	float distance = length(TangentSpace * light.position - fragPos);
	float attenuation = light.intensity / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	attenuation = (attenuation - cutoff) / (1 - cutoff);
	attenuation = max(attenuation, 0.0);
	
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}																																
		
)";

	/* TODO: Add a Blin-Phong Shader */

	Shader * defaultShader2D()
	{
		Shader* temp = ShaderManager::Get("DefaultShader2D");

		if (temp == nullptr) 
		{ 
			return Shader::CreateFromSource("DefaultShader2D", defaultShader2DSource); 
		}
		else
		{
			return temp;
		}
	}

	Shader * flatColourShader()
	{
		Shader* temp = ShaderManager::Get("FlatColourShader");

		if (temp == nullptr)
		{
			return Shader::CreateFromSource("FlatColourShader", flatColourShaderSource); 
		}
		else
		{
			return temp;
		}
	}

	Shader * blinPhongShader()
	{
		Shader* temp = ShaderManager::Get("BlinPhongShader");

		if (temp == nullptr)
		{
			return Shader::CreateFromSource("BlinPhongShader", blinPhongShaderSource); 
		}
		else
		{
			return temp;
		}
	}
}