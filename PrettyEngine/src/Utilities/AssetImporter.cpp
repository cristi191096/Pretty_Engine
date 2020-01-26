#include "pepch.h"
#include "AssetImporter.h"


#include "engine\Graphics\Texture2D.h"
#include "engine\Graphics\Mesh.h"

//--------- Level Importer Includes ------------
#include "engine\Core\Scene2D.h"
#include "engine\Core\Scene3D.h"
#include "engine\ECS\Entity.h"
#include "engine\ECS\Components\Components.h"
#include "engine\Graphics\Cameras\EditorCamera.h"

#include "String.h"

 //<FieldOfView>60</FieldOfView>
 //   <AspectRatio>1.77</AspectRatio>
 //   <ClipPlanes>1.0 1000.0</ClipPlanes>
 //<FieldOfView>60</FieldOfView>
 //   <AspectRatio>1.77</AspectRatio>
 //   <ClipPlanes>1.0 1000.0</ClipPlanes>
 //<FieldOfView>60</FieldOfView>
 //   <AspectRatio>1.77</AspectRatio>
 //   <ClipPlanes>1.0 1000.0</ClipPlanes>

namespace PrettyEngine {

#pragma region MESH IMPORTER

	MeshImporter* MeshImporter::s_Instance = new MeshImporter();

	static aiTextureType TextureTypeToAssimp(TextureType texType) 
	{
		switch (texType)
		{
		case TextureType::Diffuse:		return aiTextureType_DIFFUSE;
		case TextureType::Specular:		return aiTextureType_SPECULAR;
		case TextureType::Normal:		return aiTextureType_NORMALS;
		case TextureType::Height:		return aiTextureType_HEIGHT;
		case TextureType::Emissive:		return aiTextureType_EMISSIVE;
		case TextureType::Roughness:	return aiTextureType_DIFFUSE_ROUGHNESS;

		default:
			return aiTextureType_UNKNOWN;
		}
	}

		static TextureType AssimpToTextureType(aiTextureType texType) 
	{
		switch (texType)
		{
		case aiTextureType_DIFFUSE:					return TextureType::Diffuse;
		case aiTextureType_SPECULAR:				return TextureType::Specular;
		case aiTextureType_NORMALS:					return TextureType::Normal;
		case aiTextureType_HEIGHT:					return TextureType::Height;
		case aiTextureType_EMISSIVE:				return TextureType::Emissive;
		case aiTextureType_DIFFUSE_ROUGHNESS:		return TextureType::Roughness;

		default:
			return TextureType::None;
		}
	}

	MeshImporter::MeshImporter()
	{

	}

	MeshImporter::~MeshImporter()
	{
	}


	//return verts indices
	std::vector<MeshData> MeshImporter::Load(String & filePath, bool importTextures, bool importAnimation)
	{

		std::vector<MeshData> output;
		scene = import.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);


		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			//cout << "error assimp : " << import.GetErrorString() << endl;
			PE_CORE_ERROR("MeshImporter: {0}", import.GetErrorString());
			return output;
		}

		std::vector<String> folders = SplitString(filePath, "\\");
		String newPath;
		if (folders.size() > 1)
		{
			for (int i = 0; i < folders.size(); i++)
			{
				
				if (i == folders.size() - 1)
					newPath += folders[i];
				else
				{
					newPath += folders[i] + "/";
				}
			}
		}
		else
		{
			newPath = filePath;
		}
		filePath = newPath;
		directory = newPath.substr(0, newPath.find_last_of('/'));



		//output.push_back(processMesh(ai_mesh));
		if (importTextures) {
			//LoadTextures(ai_mesh, TextureType::Diffuse, output[i].materialMaps);
			//LoadTextures(ai_mesh, TextureType::Specular, output[i].materialMaps);
			//LoadTextures(ai_mesh, TextureType::Normal, output[i].materialMaps);
			getTextures = true;
		}
		if (importAnimation)
		{
			getBones = true;
			//Do stuff!
		}

		processNode(scene->mRootNode, output);

		return output;

	}

	void MeshImporter::processNode(aiNode * node, std::vector<MeshData>& meshes)
	{
		// process each mesh located at the current node
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			// the node object only contains indices to index the actual objects in the scene. 
			// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			MeshData tempMesh = processMesh(mesh);
			meshes.push_back(tempMesh);
		}
		// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], meshes);
		}
	}

	MeshData MeshImporter::processMesh(aiMesh * mesh)
	{
		//	std::cout << "bones: " << mesh->mNumBones << " vertices: " << mesh->mNumVertices << std::endl;

		std::vector<Vertex> vertices;
		std::vector<uint> indices;
		BB2D bb;

		std::vector<Texture2D*> textures;
		//vector<Texture> textures;
		//vector<VertexBoneData> bones_id_weights_for_each_vertex;
		

		vertices.reserve(mesh->mNumVertices);
		indices.reserve(mesh->mNumVertices);
		float minX = FLT_MAX;
		float minY = FLT_MAX;
		float maxX = -FLT_MAX;
		float maxY = -FLT_MAX;
		//bones_id_weights_for_each_vertex.resize(mesh->mNumVertices);

		//vertices
		for (uint i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			Vector3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;

			if (minX > vertex.position.x)
				minX = vertex.position.x;
			if (minY > vertex.position.y)
				minY = vertex.position.y;
			if (maxX < vertex.position.x)
				maxX = vertex.position.x;
			if (maxY < vertex.position.y)
				maxY = vertex.position.y;

			if (mesh->mNormals != NULL)
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.normal = vector;
			}
			else
			{
				vertex.normal = Vector3();
			}


			// in assimp model can have 8 different texture coordinates
			// we only care about the first set of texture coordinates
			if (mesh->mTextureCoords[0])
			{
				Vector2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.uv = vec;
			}
			else
			{
				vertex.uv = Vector2(0.0f, 0.0f);
			}

			if (mesh->mTangents != NULL) {
				vector.x = mesh->mTangents->x;
				vector.y = mesh->mTangents->y;
				vector.z = mesh->mTangents->z;
				vertex.tangent = vector;
			}
			else
			{
				vertex.tangent = Vector3();
			}

			if (mesh->mBitangents != NULL) {
				vector.x = mesh->mBitangents->x;
				vector.y = mesh->mBitangents->y;
				vector.z = mesh->mBitangents->z;

				vertex.bitangent = vector;
			}
			else
			{
				vertex.bitangent = Vector3();
			}

			vertices.push_back(vertex);
		}

		bb.min = Vector2(minX, minY);
		bb.max = Vector2(maxX, maxY);

		//indices
		for (uint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (uint j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		//material
		if (getTextures) {
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			

			std::vector<Texture2D*> diffuseMaps = LoadTextures(material, TextureType::Diffuse);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			// 2. specular maps
			std::vector<Texture2D*> specularMaps = LoadTextures(material, TextureType::Specular);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			// 3. normal maps
			std::vector<Texture2D*> normalMaps = LoadTextures(material, TextureType::Height);
			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
			// 4. height maps

		}

#if 0
		// load bones
		/*for (uint i = 0; i < mesh->mNumBones; i++)
		{
			uint bone_index = 0;
			string bone_name(mesh->mBones[i]->mName.data);

			cout << mesh->mBones[i]->mName.data << endl;

			if (m_bone_mapping.find(bone_name) == m_bone_mapping.end())
			{
				// Allocate an index for a new bone
				bone_index = m_num_bones;
				m_num_bones++;
				BoneMatrix bi;
				m_bone_matrices.push_back(bi);
				m_bone_matrices[bone_index].offset_matrix = mesh->mBones[i]->mOffsetMatrix;
				m_bone_mapping[bone_name] = bone_index;

				//cout << "bone_name: " << bone_name << "			 bone_index: " << bone_index << endl;
			}
			else
			{
				bone_index = m_bone_mapping[bone_name];
			}

			for (uint j = 0; j < mesh->mBones[i]->mNumWeights; j++)
			{
				uint vertex_id = mesh->mBones[i]->mWeights[j].mVertexId;
				float weight = mesh->mBones[i]->mWeights[j].mWeight;
				bones_id_weights_for_each_vertex[vertex_id].addBoneData(bone_index, weight);


				//cout << " vertex_id: " << vertex_id << "	bone_index: " << bone_index << "		weight: " << weight << endl;
			}
		}*/
#endif
		return { vertices, indices, textures, bb};
	}



	std::vector<Texture2D*> MeshImporter::LoadTextures(aiMaterial* mat, TextureType texType)
	{

		std::vector<Texture2D*> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(TextureTypeToAssimp(texType)); i++) {

		aiString str;
		mat->GetTexture(TextureTypeToAssimp(texType), i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++) 
		{
			if (std::strcmp(textures_loaded[j]->GetName().data(), str.C_Str()) == 0) 
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip) {
			String filename = String(str.C_Str());
			filename = directory + '/' + filename;
			Texture2D* texture = Texture2D::CreateFromFile(String(str.C_Str()) ,filename, TextureParameters(TextureWrap::REPEAT, texType), TextureLoadOptions(false, false));		//Read texture with stb_image
		
			
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}

	if (textures.size() == 0) {
		textures.push_back(Texture2D::Create(1, 1, TextureParameters(TextureWrap::REPEAT, texType), TextureLoadOptions(false, false)));
	}

	return textures;

	}

#pragma endregion

#pragma region LEVEL IMPORTER

	LevelManager* LevelManager::s_Instance = new LevelManager();

	LevelManager::LevelManager()
	{
	}

	LevelManager::~LevelManager()
	{
	}

	bool LevelManager::OpenFile(const char* filePath)
	{
		xmlDocument.LoadFile(filePath);

		if (xmlDocument.ErrorID() != NULL) {
			PE_ERROR("LEVEL PARSER: The file at: {0} couldn't be opened!", filePath);
			return false;
		}

		return true;
	}

	//========================================Import================================================

	Scene* LevelManager::Import(const char* filePath)
	{
		return s_Instance->ImportInternal(filePath);
	}

	Scene* LevelManager::ImportInternal(const char* filePath)
	{

		Scene* outputScene = nullptr;
		
		if (!OpenFile(filePath))	return outputScene;

		tinyxml2::XMLNode* root = xmlDocument.RootElement();

		//tinyxml2::XMLNode* sceneNode = root->FirstChildElement("Scene");

		tinyxml2::XMLNode* cameraNode = root->FirstChildElement("Camera");

		
		
		Camera* camera = nullptr;

		if (String(cameraNode->ToElement()->FindAttribute("type")->Value()) == "EditorCamera")
		{
			std::vector<String> camPos = SplitString(cameraNode->FirstChildElement("Position")->FirstChild()->Value(), " ");
			Vector3 cameraPosition = Vector3(std::stof(camPos[0]), std::stof(camPos[1]), std::stof(camPos[2]));

			std::vector<String> camProjection = SplitString(cameraNode->FirstChildElement("Projection")->FirstChild()->Value(), " ");
		
			float elem[4 * 4];
		
			for (int i = 0; i < 16; i++)
			{
				if (camProjection.size() != 16) {
					PE_ERROR("LEVEL PARSER: Camera Projection Matrix couldn't be parsed! Please check the XML file: {0}", filePath);
					break;
				}
				elem[i] = std::stof(camProjection[i]);
			}
		
			Matrix4 projection = Matrix4(elem);
		
			camera = new EditorCamera(cameraPosition, projection);

		//	if (String(cameraNode->ToElement()->FindAttribute("projection")->Value()) == "Perspective")
		//	{
		//		float fov = std::stof(cameraNode->FirstChildElement("FieldOfView")->FirstChild()->Value());
		//		float aspectRatio = std::stof(cameraNode->FirstChildElement("AspectRatio")->FirstChild()->Value());
		//
		//		std::vector<String> clipPlanes = SplitString(cameraNode->FirstChildElement("ClipPlanes")->FirstChild()->Value(), " ");
		//		float camNear = std::stof(clipPlanes[0]);
		//		float camFar = std::stof(clipPlanes[1]);
		//
		//		camera = new EditorCamera(cameraPosition, Matrix4::Perspective(fov, aspectRatio, camNear, camFar));
		//	}
		//	else if (String(cameraNode->ToElement()->FindAttribute("projection")->Value()) == "Orthographic")
		//	{
		//		// TODO: Parse Orthographic camera
		//
		//	}


		}

		if (String(root->ToElement()->FindAttribute("type")->Value()) == "3D")
			outputScene = new Scene3D(camera);
		else if (String(root->ToElement()->FindAttribute("type")->Value()) == "2D")
			outputScene = new Scene2D(camera);
		

		//tinyxml2::XMLNode* rendererNode = sceneNode->FirstChildElement("Renderer");			// Not necessary 

		tinyxml2::XMLNode* entityNode = root->FirstChildElement("Entity");

		while (entityNode != nullptr) 
		{
			PE_TRACE("EntityNode: {0}", entityNode->Value());

			String tag = entityNode->ToElement()->FindAttribute("tag")->Value();
			String name = entityNode->ToElement()->FindAttribute("name")->Value();

			

			Entity* entity = new Entity(name, tag);

			ProcessComponents(entityNode, entity);

			outputScene->Add(entity);

			entityNode = entityNode->NextSibling();

		}

		outputScene->SetLevelPath(filePath);

		return outputScene;
	}

	void LevelManager::ProcessComponents(tinyxml2::XMLNode* entityNode, Entity* entity)
	{
		tinyxml2::XMLNode* componentNode = entityNode->FirstChildElement();

		Transform* tr = entity->GetComponent<Transform>();

		while (componentNode != nullptr)
		{
			Component* component = nullptr;

			if (String(componentNode->Value()) == "Transform")
			{
				std::vector<String> pos = SplitString(componentNode->FirstChildElement("Position")->FirstChild()->Value(), " ");
				int b = 5;
				Vector3 position = Vector3(std::stof(pos[0]), std::stof(pos[1]), std::stof(pos[2]));
				std::vector<String> rot = SplitString(componentNode->FirstChildElement("Rotation")->FirstChild()->Value(), " ");
				Vector3 rotation;
				if (String(componentNode->FirstChildElement("Rotation")->ToElement()->FindAttribute("type")->Value()) == "EulerAngles")
				{
					rotation.x = std::stof(rot[0]);
					rotation.y = std::stof(rot[1]);
					rotation.z = std::stof(rot[2]);
				}


				std::vector<String> sc = SplitString(componentNode->FirstChildElement("Scale")->FirstChild()->Value(), " ");
				Vector3 scale(std::stof(sc[0]), std::stof(sc[1]), std::stof(sc[2]));

				
				tr->position = position;
				tr->rotation = rotation;
				tr->scale = scale;
			}
			else if (String(componentNode->Value()) == "Light")
			{
				float radius, intensity;
				Light::Type lightType;

				if (String(componentNode->ToElement()->FindAttribute("type")->Value()) == "Directional")
				{
					std::vector<String> dir = SplitString(componentNode->FirstChildElement("Direction")->FirstChild()->Value(), " ");
					tr->rotation.x = std::stof(dir[0]);
					tr->rotation.y = std::stof(dir[1]);
					tr->rotation.z = std::stof(dir[2]);
					lightType = Light::Type::DIRECTIONAL;
				}
				else if (String(componentNode->ToElement()->FindAttribute("type")->Value()) == "Point")
				{
					std::vector<String> pos = SplitString(componentNode->FirstChildElement("Positon")->FirstChild()->Value(), " ");
					tr->position.x = std::stof(pos[0]);
					tr->position.y = std::stof(pos[1]);
					tr->position.z = std::stof(pos[2]);

					radius = std::stof(componentNode->FirstChildElement("Radius")->FirstChild()->Value());
					intensity = std::stof(componentNode->FirstChildElement("Intensity")->FirstChild()->Value());

					lightType = Light::Type::POINT;

				}

				//Colours

				std::vector<String> amb		= SplitString(componentNode->FirstChildElement("Ambient")->FirstChild()->Value(), " ");
				std::vector<String> diff	= SplitString(componentNode->FirstChildElement("Diffuse")->FirstChild()->Value(), " ");
				std::vector<String> spec	= SplitString(componentNode->FirstChildElement("Specular")->FirstChild()->Value(), " ");

				Vector3 ambient(std::stof(amb[0]), std::stof(amb[1]), std::stof(amb[2]));
				Vector3 diffuse(std::stof(diff[0]), std::stof(diff[1]), std::stof(diff[2]));
				Vector3 specular(std::stof(spec[0]), std::stof(spec[1]), std::stof(spec[2]));

				component = new LightComponent(lightType, diffuse, ambient, specular, intensity, radius);

			}
			else if (String(componentNode->Value()) == "Model")
			{
				String file = componentNode->ToElement()->FindAttribute("filePath")->Value();

				// TODO: Add support for buffer usage and animations. 

				//Parsing Material.
				tinyxml2::XMLNode* materialNode = componentNode->FirstChildElement("Material");
				Material* material = nullptr;
				String shaderFile = materialNode->FirstChildElement("Shader")->ToElement()->FindAttribute("filePath")->Value();
				
				std::vector<String> diff	= SplitString(materialNode->FirstChildElement("Diffuse")->FirstChild()->Value(), " ");
				std::vector<String> spec	= SplitString(materialNode->FirstChildElement("Specular")->FirstChild()->Value(), " ");
				std::vector<String> em		= SplitString(materialNode->FirstChildElement("Emission")->FirstChild()->Value(), " ");

				Vector3 diffuse(std::stof(diff[0]), std::stof(diff[1]), std::stof(diff[2]));
				Vector3 specular(std::stof(spec[0]), std::stof(spec[1]), std::stof(spec[2]));
				Vector3 emission(std::stof(em[0]), std::stof(em[1]), std::stof(em[2]));
				float shininess = std::stof(materialNode->FirstChildElement("Shininess")->FirstChild()->Value());


				 // filePath = None is default. Work in progress: custom shader (Materials need refactoring) >> You can either write a custom shader within the component (or load it from file) or use a predefined shader from the engine: Flat, BlinPhong,(Note: 2D should have a different structure) Quad2D 
				if (shaderFile != "None")
				{
					material = new Material(Shader::CreateFromFile("CustomShader", shaderFile));
				}
				else
				{
					if (ToLowerCase( String(materialNode->FirstChildElement("Shader")->FirstChild()->Value())) == "blinphong")
					{
						material = new Material(blinPhongShader());
					}
					else if (ToLowerCase( String(materialNode->FirstChildElement("Shader")->FirstChild()->Value())) == "flat")
					{
						material = new Material(flatColourShader());
					}
					else 
					{
						material = new Material(Shader::CreateFromSource("CustomShader", materialNode->FirstChildElement("Shader")->FirstChild()->Value()));
					}
				}

				component = new ModelComponent(new Model(file, material));

			}
			else if (String(componentNode->Value()) == "Rigidbody")
			{
				float density = std::stof(componentNode->FirstChildElement("Density")->FirstChild()->Value());
				float drag = std::stof(componentNode->FirstChildElement("Drag")->FirstChild()->Value());
				BodyType type;

				if (ToLowerCase(componentNode->ToElement()->FindAttribute("type")->Value()) == "dynamic")
					type = BodyType::DYNAMIC;
				else if (ToLowerCase(componentNode->ToElement()->FindAttribute("type")->Value()) == "static")
					type = BodyType::STATIC;
				else if (ToLowerCase(componentNode->ToElement()->FindAttribute("type")->Value()) == "kinematic")
					type = BodyType::KINEMATIC;

				component = new Rigidbody(density, drag, type);
			}



			entity->AddComponent(component);
			componentNode = componentNode->NextSibling();
		}

		
	}

	//=====================================Export=============================================

	void LevelManager::Export(const char * filePath, Scene* scene)
	{
		s_Instance->ExportInternal(filePath, scene);
	}

	void LevelManager::ExportInternal(const char * filePath, Scene* scene)
	{
		xmlDocument.Clear();

		tinyxml2::XMLNode* declaration = xmlDocument.NewDeclaration("xml version=\"1.0\" encoding=\"utf-8\"");

		xmlDocument.InsertEndChild(declaration);

		tinyxml2::XMLNode* sceneNode = xmlDocument.NewElement("Scene");
		String sceneType;
		if (dynamic_cast<Scene3D*>(scene))
			sceneType = "3D";
		else if (dynamic_cast<Scene2D*>(scene))
			sceneType = "2D";
		sceneNode->ToElement()->SetAttribute("type", sceneType.c_str());

		tinyxml2::XMLNode* cameraNode = xmlDocument.NewElement("Camera");

		if (dynamic_cast<EditorCamera*>(scene->GetCamera()))
			cameraNode->ToElement()->SetAttribute("type", "EditorCamera");

		tinyxml2::XMLNode* cameraPos = xmlDocument.NewElement("Position"); 
		tinyxml2::XMLNode* cameraProjection = xmlDocument.NewElement("Projection"); 

		cameraPos->ToElement()->SetText(scene->GetCamera()->GetPosition().Export().c_str());
		cameraProjection->ToElement()->SetText(scene->GetCamera()->GetProjectionMatrix().Export().c_str());

		if (sceneType == "3D")
		{
			std::vector<Entity*> entities = scene->GetEntities<Entity>();
			for (int i = 0; i < entities.size(); i++)
			{
				String entityName;
				if (entities[i]->name == "Entity")
					entityName = entities[i]->name + std::to_string(i);
				else
					entityName = entities[i]->name;
				tinyxml2::XMLNode* entityNode = xmlDocument.NewElement("Entity");
				entityNode->ToElement()->SetAttribute("name", entityName.c_str());
				entityNode->ToElement()->SetAttribute("tag", entities[i]->tag.c_str());

				Transform* transform = entities[i]->GetComponent<Transform>();

				if (transform != nullptr)
				{
					//Transform parsing
					tinyxml2::XMLNode* componentNode = xmlDocument.NewElement("Transform");

					tinyxml2::XMLNode* positionNode = xmlDocument.NewElement("Position");
					tinyxml2::XMLNode* rotationNode = xmlDocument.NewElement("Rotation");
					tinyxml2::XMLNode* scaleNode	= xmlDocument.NewElement("Scale");

					positionNode->ToElement()->SetText(transform->position.Export().c_str());
					rotationNode->ToElement()->SetAttribute("type", "EulerAngles");
					rotationNode->ToElement()->SetText(transform->rotation.Export().c_str());
					scaleNode->ToElement()->SetText(transform->scale.Export().c_str());

					componentNode->InsertEndChild(positionNode);
					componentNode->InsertEndChild(rotationNode);
					componentNode->InsertEndChild(scaleNode);
					entityNode->InsertEndChild(componentNode);
				}

				ModelComponent* modelComp = entities[i]->GetComponent<ModelComponent>();

				if (modelComp != nullptr)
				{
					//Model parsing
					tinyxml2::XMLNode* componentNode = xmlDocument.NewElement("Model");
					componentNode->ToElement()->SetAttribute("filePath", modelComp->model->GetFilePath().c_str());

					tinyxml2::XMLNode* materialNode = xmlDocument.NewElement("Material");

					tinyxml2::XMLNode* shaderNode = xmlDocument.NewElement("Shader");
					Material* material = modelComp->model->GetMeshes()[0]->GetMaterial();
					shaderNode->ToElement()->SetAttribute("filePath", material->GetShader()->GetFilePath().c_str());
					switch (material->GetShader()->GetType())
					{
					case Shader::Type::BLINPHONG:
					{
						shaderNode->ToElement()->SetText("BLINPHONG");
						break;
					}
					case Shader::Type::FLAT:
					{
						shaderNode->ToElement()->SetText("FLAT");
						break;
					}
					default:
						break;
					}

					tinyxml2::XMLNode* diffuseNode	= xmlDocument.NewElement("Diffuse");
					tinyxml2::XMLNode* specularNode = xmlDocument.NewElement("Specular");
					tinyxml2::XMLNode* emissionNode	= xmlDocument.NewElement("Emission");
					tinyxml2::XMLNode* shineNode	= xmlDocument.NewElement("Shininess");

				
					diffuseNode->ToElement()->SetText(material->GetDiffuseColour().Export().c_str());
					specularNode->ToElement()->SetText(material->GetSpecularColour().Export().c_str());
					emissionNode->ToElement()->SetText(material->GetEmissionColour().Export().c_str());
					shineNode->ToElement()->SetText(material->GetShininess());

					materialNode->InsertFirstChild(shaderNode);
					materialNode->InsertEndChild(diffuseNode);
					materialNode->InsertEndChild(specularNode);
					materialNode->InsertEndChild(emissionNode);
					materialNode->InsertEndChild(shineNode);
					componentNode->InsertEndChild(materialNode);
					entityNode->InsertEndChild(componentNode);
				}

				LightComponent* lightComp = entities[i]->GetComponent<LightComponent>();

				if (lightComp != nullptr)
				{
					//Light parsing
					tinyxml2::XMLNode* componentNode = xmlDocument.NewElement("Light");

					if (lightComp->m_Type == Light::Type::DIRECTIONAL)
					{
						componentNode->ToElement()->SetAttribute("type", "Directional");
						tinyxml2::XMLNode* directionNode = xmlDocument.NewElement("Direction");
						directionNode->ToElement()->SetText(lightComp->light->m_Direction.Export().c_str());

						componentNode->InsertFirstChild(directionNode);
					}
					else if (lightComp->m_Type == Light::Type::POINT)
					{
						componentNode->ToElement()->SetAttribute("type", "Point");
						tinyxml2::XMLNode* positionNode = xmlDocument.NewElement("Position");
						tinyxml2::XMLNode* intensityNode = xmlDocument.NewElement("Intensity");
						tinyxml2::XMLNode* radiusNode = xmlDocument.NewElement("Radius");

						positionNode->ToElement()->SetText(lightComp->light->m_Position.Export().c_str());
						intensityNode->ToElement()->SetText(lightComp->light->m_Intensity);
						radiusNode->ToElement()->SetText(lightComp->light->m_Radius);

						componentNode->InsertFirstChild(positionNode);
						componentNode->InsertEndChild(intensityNode);
						componentNode->InsertEndChild(radiusNode);
					}

					tinyxml2::XMLNode* ambientNode	= xmlDocument.NewElement("Ambient");
					tinyxml2::XMLNode* diffuseNode	= xmlDocument.NewElement("Diffuse");
					tinyxml2::XMLNode* specularNode = xmlDocument.NewElement("Specular");

					ambientNode->ToElement()->SetText(lightComp->light->m_Ambient.Export().c_str());
					diffuseNode->ToElement()->SetText(lightComp->light->m_Diffuse.Export().c_str());
					specularNode->ToElement()->SetText(lightComp->light->m_Specular.Export().c_str());

					componentNode->InsertEndChild(ambientNode);
					componentNode->InsertEndChild(diffuseNode);
					componentNode->InsertEndChild(specularNode);
					entityNode->InsertEndChild(componentNode);

				}

				Rigidbody* rigidbody = entities[i]->GetComponent<Rigidbody>();

				if (rigidbody != nullptr)
				{
					//Rigidbody parsing
					tinyxml2::XMLNode* componentNode = xmlDocument.NewElement("Rigidbody");
					
					switch (rigidbody->GetBodyType())
					{
					case BodyType::DYNAMIC:
						{
							componentNode->ToElement()->SetAttribute("type", "Dynamic");
							break;
						}
					case BodyType::STATIC:
						{
							componentNode->ToElement()->SetAttribute("type", "Static");
							break;
						}
					case BodyType::KINEMATIC:
						{
							componentNode->ToElement()->SetAttribute("type", "Kinematic");
							break;
						}
					default:
						break;
					}

					tinyxml2::XMLNode* densityNode = xmlDocument.NewElement("Density");
					tinyxml2::XMLNode* dragNode = xmlDocument.NewElement("Drag");

					densityNode->ToElement()->SetText(std::to_string(rigidbody->m_Density).c_str());
					dragNode->ToElement()->SetText(rigidbody->m_Drag);

					componentNode->InsertEndChild(densityNode);
					componentNode->InsertEndChild(dragNode);
					entityNode->InsertEndChild(componentNode);
				}

				sceneNode->InsertEndChild(entityNode);
			}
		}
		else if (sceneType == "2D")
		{
			for (int i = 0; i < scene->GetEntities<Renderable2D>().size(); i++)
			{
				// TODO:
			}
		}

		//=====Inserts=============
		cameraNode->InsertEndChild(cameraPos);
		cameraNode->InsertEndChild(cameraProjection);
		sceneNode->InsertFirstChild(cameraNode);
		xmlDocument.InsertEndChild(sceneNode);

		if (xmlDocument.SaveFile(filePath) != tinyxml2::XML_SUCCESS)
		{
			PE_ERROR("The exported file at path: {0} couldn't be saved on disk", filePath);
		}
	}


#pragma endregion
}


