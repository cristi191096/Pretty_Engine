#pragma once
#include "engine\Core\Layer.h"
#include "engine\Graphics\Shaders\Shader.h"
#include "engine\ECS\Components\Component.h"


namespace PrettyEngine {

	
	class Model;
	class Component;

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		~EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;

		void Begin();
		void End();
		void ProfilerTab(bool* show);

	private:
		bool m_NewScene = false;
		Vector3 m_InitialCameraPosition = Vector3(0.0f, 0.0f, -50.0f);
		Matrix4 m_CameraProjection = Matrix4::Perspective(60.0f, (float)1280 / (float)720, 1.0f, 1000.0f);
		std::vector<bool*> entityTabs;

	private:
		const char* OpenFileDialog();
		const char* SaveFileDialog();

		void SaveCurrentScene();

		void DockSpace();
		bool SaveConfirmationTab(bool* show);
		void MainMenuBar();
		void SceneTab();
		void EntityTab(Entity* entity, bool* show);

		void UpdateModelMaterial(Model* model, Shader::Type shaderType, const Vector3& diffuse, const Vector3& specular, const Vector3& emission, const float& shininess);
		

	};
}