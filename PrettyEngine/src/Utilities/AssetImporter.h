#pragma once
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <tinyxml2.h>
#include "engine\Maths\Vector2.h"

//#define ASSIMP_BUILD_BOOST_WORKAROUND

namespace PrettyEngine {

	struct Vertex;
	class Texture2D;
	class Scene;
	class Entity;
	enum class TextureType;

	struct BB2D {
		Vector2 min;
		Vector2 max;
	};	  // Used to build physics colliders

	struct MeshData {
		std::vector<Vertex> vertices;
		std::vector<uint> indices;
		std::vector<Texture2D*> materialMaps;
		BB2D boundingBoxData;
	};

	class MeshImporter
	{
	public:
		std::vector<MeshData> Load(String& filePath, bool importTextures = false, bool importAnimation = false);
		static MeshImporter* Get() { return s_Instance; }

	private:
		MeshImporter();
		~MeshImporter();
		static MeshImporter* s_Instance;
		Assimp::Importer import;
		const aiScene* scene;
		String directory;

	private:
		bool getTextures = false;
		bool getBones = false;
		std::vector<Texture2D*> textures_loaded;

		void processNode(aiNode* node, std::vector<MeshData>& meshes);
		MeshData processMesh(aiMesh* mesh);
		//Material* LoadMaterial(aiMaterial* mat, aiTextureType type, String type_name);
		std::vector<Texture2D*> MeshImporter::LoadTextures(aiMaterial* mat, TextureType texType);


	};

	class AudioImporter
	{

	};


	class LevelManager
	{

	public:
		static LevelManager* Get() { return s_Instance; }
		static Scene* Import(const char* filePath);
		static void Export(const char* filePath, Scene* scene);

	private:
		LevelManager();
		~LevelManager();
		Scene* ImportInternal(const char* filePath);
		void ExportInternal(const char* filePath, Scene* scene);
		void ProcessComponents(tinyxml2::XMLNode* entityNode, Entity* entity);
		bool OpenFile(const char* filePath);

	private:
		tinyxml2::XMLDocument xmlDocument;
		static LevelManager* s_Instance;
	};

}