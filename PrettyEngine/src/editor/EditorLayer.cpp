#include "pepch.h"
#include "EditorLayer.h"

#include "engine\Core\Application.h"

// GUI includes
#include "imgui.h"
#include "examples\imgui_impl_opengl3.h"
#include "examples\imgui_impl_glfw.h"
#include "imgui_stdlib.h"

#include <GLFW\glfw3.h>

#include <nfd.h>
//=======================
#include "engine\Graphics\Cameras\EditorCamera.h"
#include "Utilities\AssetImporter.h"
#include "engine\Core\Scene3D.h"
#include "engine\ECS\Components\Components.h"
#include "engine\Events\Input.h"
#include "Utilities\String.h"

namespace PrettyEngine {


	static bool saveTab = false;
	static bool newScene = false;
	static bool openScene = false;
	static bool showProfiler = false;
	static int currentNumberEntities = 0;
	static std::vector<float> audioProfileDuration;
	static std::vector<float> drawProfileDuration;
	static std::vector<float> GUIProfileDuration;
	static std::vector<float> physicsProfileDuration;

	EditorLayer::EditorLayer() : Layer ("Editor")
	{
		
		m_Scene = new Scene3D(new EditorCamera(m_InitialCameraPosition, m_CameraProjection));

	}
	EditorLayer::~EditorLayer() 
	{

	}

	void EditorLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Platform/Renderer bindings
		//ImGui_ImplGlfw_InitForOpenGL(window, true);
		//ImGui_ImplOpenGL3_Init(glsl_version);

		// Setup Style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;                                // When viewports are enabled it is preferable to disable WinodwRounding
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;                   // When viewports are enabled it is preferable to disable WindowBg alpha
		}

		GLFWwindow* window = static_cast<GLFWwindow*>(Context::Get()->GetNativeContext());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

	}
	void EditorLayer::OnDetach()
	{
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	
#pragma region FILESYSTEM MANAGEMENT

	const char* EditorLayer::OpenFileDialog()
	{
		nfdchar_t *outPath = NULL;
		
		nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);
		if (result == NFD_OKAY)
		{
			
			return outPath;
		}
		else if (result == NFD_CANCEL) {
			PE_INFO("User pressed cancel.");
		}
		else {
			PE_ERROR("Error Opening file: {0}", NFD_GetError());
		}

		return "NULL";
	}

	const char* EditorLayer::SaveFileDialog()
	{
		nfdchar_t *outPath = NULL;
		
		nfdresult_t result = NFD_SaveDialog("xml", NULL, &outPath);
		if (result == NFD_OKAY)
		{
			
			return outPath;
			//std::size_t found = out.find("PrettyEngine");
			//if (found != std::string::npos)
			//{
			//	out = out.substr(found + 1);
			//}
		}
		else if (result == NFD_CANCEL) {
			PE_INFO("User pressed cancel.");
		}
		else {
			PE_ERROR("Error Opening file: {0}", NFD_GetError());
		}

		return "NULL";
	}

	void EditorLayer::SaveCurrentScene()
	{
		const char* filePath;
			if (m_Scene->GetLevelPath() == "NULL")
			{
				filePath = SaveFileDialog();
			}
			else
			{
				filePath = m_Scene->GetLevelPath().c_str();
			}
			if (filePath != "NULL")
			{
				LevelManager::Export(filePath, m_Scene);
			}
	}

#pragma endregion Methods that allown manipulating files in your system

#pragma region EDITOR DRAWING
	void EditorLayer::DockSpace()
	{
	

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
  
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
   

    // When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::Begin("DockSpace Demo", NULL, window_flags);

   

    ImGui::End();
	}

	bool EditorLayer::SaveConfirmationTab(bool* show)
	{
		if (*show) {
			if (!ImGui::Begin("Confirm Save!", show))
			{
				ImGui::End();
				return false;
			}

			ImGui::Text("Do you want to save this scene?\n Note: Please make sure it's xml format.");
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			if (ImGui::Button("Save")) {
				SaveCurrentScene();
				*show = false;
				ImGui::End();
				return true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Don't Save")) {
				*show = false;
				ImGui::End();
				return true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel")) {
				*show = false;
				ImGui::End();
				return false;
			}
			ImGui::End();

		}
		return false;
	}

	void EditorLayer::MainMenuBar()
	{
		Application::Get().UseEditor(true);
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{

				if (ImGui::MenuItem("New Scene"))
				{
					saveTab = true;
					newScene = true;
					openScene = false;
					//m_Scene = nullptr;
				}
				if (ImGui::MenuItem("Open Scene", "Ctrl+O"))
				{
					saveTab = true;
					openScene = true;
					newScene = false;
				}


				if (ImGui::MenuItem("Save", "Ctrl+S"))
				{
					SaveCurrentScene();
				}
				if (ImGui::MenuItem("Save As.."))
				{
					const char* filePath = SaveFileDialog();
					if (filePath != "NULL")
					{
						LevelManager::Export(filePath, m_Scene);
					}
				}
				if (ImGui::MenuItem("Quit", "Esc"))
				{
					Application::Get().ShouldRun(false);
				}

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Profiler"))
			{
				if (ImGui::MenuItem("Open Profiler"))
				{
					showProfiler = true;
				}

				ImGui::EndMenu();
			}
		
			if (ImGui::Button("Exit Editor"))
			{
				Application::Get().UseEditor(false);
			}
		}
	
		ImGui::EndMainMenuBar();

		

		bool sceneSaved = SaveConfirmationTab(&saveTab);
		if (sceneSaved) {
			if (newScene) m_NewScene = true;
			if (openScene)
			{
				const char* filePath = OpenFileDialog();
				if (filePath != "NULL")
				{

					delete m_Scene;
					for (int i = 0; i < entityTabs.size(); i++)
					{
						delete entityTabs[i];
					}
					entityTabs.clear();

					m_Scene = LevelManager::Import(filePath);
					currentNumberEntities = m_Scene->GetEntities<Entity>().size();
					for (int i = 0; i < m_Scene->GetEntities<Entity>().size(); i++)
					{
						bool* val = new bool;
						*val = false;
						entityTabs.push_back(val);
					}
					m_Scene->Submit();
				}
			}
		}
	}

	void EditorLayer::SceneTab()
	{

		ImGui::Begin("Scene");

		ImGui::Text("Scene");
		ImGui::SameLine(); 
		if (ImGui::Button("+"))
		{
			String name = "Entity" + std::to_string(currentNumberEntities);
			m_Scene->Add(new Entity(name));
			bool* val = new bool;
			*val = false;
			entityTabs.push_back(val);
			currentNumberEntities++;
		}
		ImGui::Separator();

		std::vector<Entity*> entities = m_Scene->GetEntities<Entity>();
		float buttonWidth = ImGui::GetWindowWidth();
		
		
		for (int i = 0; i < entities.size(); i++)
		{
			if (ImGui::Button(entities[i]->name.c_str(), ImVec2(buttonWidth, 0)))
			{
				*entityTabs[i] = true;
			}

			EntityTab(entities[i], entityTabs[i]);
		}

	
		
		ImGui::End();

	
	}

	void EditorLayer::EntityTab(Entity* entity, bool* show)
	{
	//	ImGui::End();
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
		if (*show) {
			if (!ImGui::Begin(entity->name.c_str(), show, window_flags))
			{
				ImGui::End();
			}
			else
			{
				//char* name = new char[40 + 1];
				//float pos[3] = { 0,0,0 };
				//memset(name, 0, 40 + 1);
				//char* tag = new char[40];
				//ImGui::InputText("Name", &entity->name);
				ImGui::InputText(" Tag", &entity->tag);
				ImGui::Separator();
				ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
				//	//ImGui::InputText("Tag: ", tag, 40 * sizeof(char));
				Transform* transform = entity->GetComponent<Transform>();
				ImGui::Text("Transform");
				if (ImGui::DragFloat3(" Position", entity->m_Properties.position, 0.25f))
				{
					transform->position.x = entity->m_Properties.position[0];
					transform->position.y = entity->m_Properties.position[1];
					transform->position.z = entity->m_Properties.position[2];

				}
				if (ImGui::DragFloat3(" Rotation", entity->m_Properties.rotation, 0.25f))
				{
					transform->rotation.x = entity->m_Properties.rotation[0];
					transform->rotation.y = entity->m_Properties.rotation[1];
					transform->rotation.z = entity->m_Properties.rotation[2];

				}
				if (ImGui::DragFloat3(" Scale", entity->m_Properties.scale, 0.25f))
				{
					transform->scale.x = entity->m_Properties.scale[0];
					transform->scale.y = entity->m_Properties.scale[1];
					transform->scale.z = entity->m_Properties.scale[2];

				}

				ModelComponent* modelComponent = entity->GetComponent<ModelComponent>();

				if (modelComponent)
				{
					ImGui::Separator();
					ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
					ImGui::Text("Model");
					//if (ImGui::Button("...")) OpenFileDialog();
					String fileText;
					if (modelComponent->model->GetFilePath().size() > 0)
						fileText = SplitString(modelComponent->model->GetFilePath(), "/").back();
					else
						fileText = modelComponent->model->GetFilePath();
					ImGui::Text("File: "); ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 1, 0, 1), fileText.c_str());
					ImGui::SameLine(); 
					if (ImGui::Button("..."))
					{
						String filePath = OpenFileDialog();
						if (filePath != "NULL")
						{
							modelComponent->model->SetFilePath(filePath);
							modelComponent->model->Reload();
							m_Scene->Submit();
						}
					}

					ImGui::Spacing(); ImGui::Spacing();

					ImGui::Text("Material");
					static ImVec4 diff = ImColor(114, 144, 154, 255);
					static ImVec4 spec = ImColor(114, 144, 154, 255);
					static ImVec4 emis = ImColor(114, 144, 154, 255);
					if (modelComponent->model->GetMesheCount() > 0)
					{
						Material* material = modelComponent->model->GetMeshes()[0]->GetMaterial();
						diff = ImColor(material->GetDiffuseColour().x, material->GetDiffuseColour().y, material->GetDiffuseColour().z);
						spec = ImColor(material->GetSpecularColour().x, material->GetSpecularColour().y, material->GetSpecularColour().z);
						emis = ImColor(material->GetEmissionColour().x, material->GetEmissionColour().y, material->GetEmissionColour().z);
					}
					const char* shaders[] = { "BLINPHONG", "FLAT" };
					static int currentShader = 0;
					ImGui::Combo(" Shader", &currentShader, shaders, IM_ARRAYSIZE(shaders));


					
					ImGui::ColorEdit3(" Diffuse", (float*)&diff);
					ImGui::ColorEdit3(" Specular", (float*)&spec);
					ImGui::ColorEdit3(" Emissions", (float*)&emis);
					ImGui::DragFloat(" Shininess", &entity->m_Properties.shininess, 0.5f, 0.0f, 128.0f);

					UpdateModelMaterial(modelComponent->model, currentShader ? Shader::Type::FLAT : Shader::Type::BLINPHONG, Vector3(diff.x, diff.y, diff.z), Vector3(spec.x, spec.y, spec.z), Vector3(emis.x, emis.y, emis.z), entity->m_Properties.shininess);
				}

				LightComponent* lightComponent = entity->GetComponent<LightComponent>();

				if (lightComponent)
				{
					ImGui::Separator();
					ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
					ImGui::Text("Light");

					const char* lightTypes[] = { "Directional", "Point" };
					static int currentType = 0;
					ImGui::Combo(" Type", &currentType, lightTypes, IM_ARRAYSIZE(lightTypes));

					if (currentType == 0)		//Directional
					{
						lightComponent->light->m_Type = Light::Type::DIRECTIONAL;
						if (ImGui::DragFloat3(" Direction", entity->m_Properties.rotation, 0.25f))
						{
							Vector3 dir = Vector3(entity->m_Properties.rotation[0], entity->m_Properties.rotation[1], entity->m_Properties.rotation[2]);
							lightComponent->light->m_Direction = dir.Normalise();
						}
					}
					else if (currentType == 1)	//Point
					{
						lightComponent->light->m_Type = Light::Type::POINT;
						if (ImGui::DragFloat3(" Position", entity->m_Properties.position, 0.25f))
						{

							lightComponent->light->m_Position = Vector3(entity->m_Properties.position[0], entity->m_Properties.position[1], entity->m_Properties.position[2]);
						}

						ImGui::DragFloat(" Intensity", &lightComponent->light->m_Intensity, 0.5f, 0.0f, 10.0f);
						if (ImGui::DragFloat(" Radius", &lightComponent->light->m_Radius, 0.5f, 0.0f, 100.0f))
						{
							lightComponent->light->UpdateAttenuation();
						}

					}


					static ImVec4 ambi = ImColor(lightComponent->light->m_Ambient.x, lightComponent->light->m_Ambient.y, lightComponent->light->m_Ambient.z);
					static ImVec4 diff = ImColor(lightComponent->light->m_Diffuse.x, lightComponent->light->m_Diffuse.y, lightComponent->light->m_Diffuse.z);
					static ImVec4 spec = ImColor(lightComponent->light->m_Specular.x, lightComponent->light->m_Specular.y, lightComponent->light->m_Specular.z);

					ImGui::ColorEdit3(" Ambient", (float*)&ambi);
					ImGui::ColorEdit3(" Diffuse", (float*)&diff);
					ImGui::ColorEdit3(" Specular", (float*)&spec);

					lightComponent->light->m_Ambient = Vector3(ambi.x, ambi.y, ambi.z);
					lightComponent->light->m_Diffuse = Vector3(diff.x, diff.y, diff.z);
					lightComponent->light->m_Specular = Vector3(spec.x, spec.y, spec.z);

				}

				Rigidbody* rigidbody = entity->GetComponent<Rigidbody>();

				if (rigidbody)
				{
					ImGui::Separator();
					ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
					ImGui::Text("Rigidbody");

					const char* bodyTypes[] = { "Static", "Dynamic", "Kinematic" };
					static int currentType = 0;
					if (ImGui::Combo(" Type", &currentType, bodyTypes, IM_ARRAYSIZE(bodyTypes)))
					{
						if (currentType == 0)
							rigidbody->SetBodyType(BodyType::STATIC);
						if (currentType == 1)
							rigidbody->SetBodyType(BodyType::DYNAMIC);
						if (currentType == 2)
							rigidbody->SetBodyType(BodyType::KINEMATIC);
					}

					if (ImGui::DragFloat(" Density", &rigidbody->m_Density, 0.05f, 0.1f, 10.0f))
						rigidbody->SetDensity();

					if (ImGui::DragFloat(" Drag", &rigidbody->m_Drag, 0.05f, 0.1f, 10.0f))
						rigidbody->SetDrag();
				}

				ImGui::Separator();
				ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

				const char* componentTypes[] = {"None", "Model", "Rigidbody", "Light" };
				static int currentType = 0;
				ComponentType compType;
				if (ImGui::Combo(" Add Component", &currentType, componentTypes, IM_ARRAYSIZE(componentTypes)))
				{
					
					if (currentType == 1)
						entity->AddComponent(new ModelComponent(new Model()));
					if (currentType == 2)
						entity->AddComponent(new Rigidbody(0.00001f, 1.0f));
					if (currentType == 3)
						entity->AddComponent(new LightComponent(Light::Type::DIRECTIONAL));
				}

				if (ImGui::Button("Remove from Scene"))
				{
					m_Scene->Remove(entity);
					m_Scene->Submit();
				}
				//ComponentTab(entity, compType);
				ImGui::End();
			}
		}
	}


	void EditorLayer::UpdateModelMaterial(Model * model, Shader::Type shaderType, const Vector3& diffuse, const Vector3& specular, const Vector3& emission, const float& shininess)
	{
		for (int i = 0; i < model->GetMesheCount(); i++)
		{
			Material* material = model->GetMeshes()[i]->GetMaterial();

			switch (shaderType)
			{
			case 0:
			{
				material->SetShader(blinPhongShader());
				break;
			}
			case 1:
			{
				material->SetShader(flatColourShader());
				break;
			}
			default:
			{
				material->SetShader(blinPhongShader());
				break;
			}
			}

			material->SetDiffuseColour(diffuse);
			material->SetSpecularColour(specular);
			material->SetEmissionColour(emission);
			material->SetShininess(shininess);
							
						
		}
	}

#pragma endregion Methods that draws elements in the editor


	void EditorLayer::OnImGuiRender()
	{
		//DockSpace(); //>>>> Not working very well
		
		if (Application::Get().EditorInUse()) 
		{
			MainMenuBar();
			SceneTab();
			ProfilerTab(&showProfiler);
		}
	}



	void EditorLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
	}

	void EditorLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();

		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());


		//Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) 
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();		// TODO: Modularise this. Note: use context.
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void EditorLayer::ProfilerTab(bool * show)
	{
		static bool snapshot = false;

		if (*show) {
			if (!ImGui::Begin("Profiler", show))
			{
				ImGui::End();
				return;
			}

			ImGui::Text("Profiler \n\n Hover over a bar to see the time each update took."); ImGui::Separator(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
			

			for (int i = 0; i < Application::Get().GetProfileResults()->size(); i++) {

			//	PE_TRACE("Profile {0} | {1}", Application::Get().GetProfileResults()[i].name, Application::Get().GetProfileResults()[i].time);
				if (Application::Get().GetProfileResults()->at(i).name == "Audio Update")
				{
					if (!snapshot)
						audioProfileDuration.push_back(Application::Get().GetProfileResults()->at(i).time);

					ImGui::PlotHistogram(Application::Get().GetProfileResults()->at(i).name, audioProfileDuration.data(), audioProfileDuration.size(), 0, "ms", 0.0f, 2.f, ImVec2(0, 50));
				}


				if (audioProfileDuration.size() > 80)
				{
					audioProfileDuration.erase(audioProfileDuration.begin());
				}

				if (Application::Get().GetProfileResults()->at(i).name == "Layers Draw Calls")
				{
					if (!snapshot)
						drawProfileDuration.push_back(Application::Get().GetProfileResults()->at(i).time);
				
					ImGui::PlotHistogram(Application::Get().GetProfileResults()->at(i).name, drawProfileDuration.data(), drawProfileDuration.size(), 0, "ms", 0.0f, 2.f, ImVec2(0, 50));
				}


				if (drawProfileDuration.size() > 80)
				{
					drawProfileDuration.erase(drawProfileDuration.begin());
				}

				if (Application::Get().GetProfileResults()->at(i).name == "GUI Update")
				{
					if (!snapshot)
						GUIProfileDuration.push_back(Application::Get().GetProfileResults()->at(i).time);
				
					ImGui::PlotHistogram(Application::Get().GetProfileResults()->at(i).name, GUIProfileDuration.data(), GUIProfileDuration.size(), 0, "ms", 0.0f, 2.f, ImVec2(0, 50));
				}


				if (GUIProfileDuration.size() > 80)
				{
					GUIProfileDuration.erase(GUIProfileDuration.begin());
				}

				if (Application::Get().GetProfileResults()->at(i).name == "Physics Update")
				{
					if (!snapshot)
						physicsProfileDuration.push_back(Application::Get().GetProfileResults()->at(i).time);

					ImGui::PlotHistogram(Application::Get().GetProfileResults()->at(i).name, physicsProfileDuration.data(), physicsProfileDuration.size(), 0, "ms", 0.0f, 2.f, ImVec2(0, 50));
				}


				if (physicsProfileDuration.size() > 80)
				{
					physicsProfileDuration.erase(physicsProfileDuration.begin());
				}



				//ImGui::ProgressBar(result.time, ImVec2(0.0f, 0.0f), " ");
				//ImGui::pl
				
				//ImGui::SameLine(); ImGui::Text(" %.3f ms", result.time);
				ImGui::Spacing(); ImGui::Spacing();
			}

			Application::Get().GetProfileResults()->clear();

			ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

			 ImGui::Checkbox("Take a SnapShot", &snapshot);

			ImGui::End();
		}

	}

	void EditorLayer::OnUpdate()
	{
		if (m_NewScene)
		{
				delete m_Scene;
				for (int i = 0; i < entityTabs.size(); i++)
				{
					delete entityTabs[i];
				}
				entityTabs.clear();
			
			m_Scene =  new Scene3D(new EditorCamera(m_InitialCameraPosition, m_CameraProjection));
			for (int i = 0; i < m_Scene->GetEntities<Entity>().size(); i++)
			{
				bool* val = new bool;
				*val = false;
				entityTabs.push_back(val);
			}
			m_Scene->Submit();
			m_NewScene = false;
		}

		//Input Handling
		if (Input::IsModOn(Internal::mod::Control) && Input::GetKeyDown(keyCode::O))
		{
			saveTab = true;
			openScene = true;
			newScene = false;
		}

		if (Input::IsModOn(Internal::mod::Control) && Input::GetKeyDown(keyCode::S))
		{
			SaveCurrentScene();
		}

		m_Scene->RenderScene();
	}

		void EditorLayer::OnEvent(Event & event)
	{
			m_Scene->OnEvent(event);
	}

	
}