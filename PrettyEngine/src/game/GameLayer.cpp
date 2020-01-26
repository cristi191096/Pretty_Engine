#include "pepch.h"
#include "GameLayer.h"

#include "Utilities\AssetImporter.h"
#include "engine\Core\Scene3D.h"
#include "engine\Graphics\Cameras\EditorCamera.h"
#include "engine\Core\Application.h"


#include "imgui.h"
#include "editor\imgui_stdlib.h"
#include <nfd.h>

static bool showMenu = false;
static bool showLobby = false;
static bool serverShow = false;
static bool clientShow = false;
static bool showProfiler = false;
static bool showEndGame = false;
static bool showStartGame = false;
static String file;
static LevelInfo levelInfo;
static TransformData transformData;



	static const char* OpenFileDialog()
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



GameLayer::GameLayer() : Layer("Game")
{
	m_Scene = new Scene3D(new EditorCamera(Vector3(0.0f, 0.0f, -50.0f),Matrix4::Perspective(60.0f, (float)1280 / (float) 720 , 1.0f, 1000.0f)));// LevelManager::Import("src/game/res/Levels/level1.xml");
	Application::Get().UseEditor(false);
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnAttach()
{
	m_BackgroundMusic = new Audio("../PrettyEngine/src/game/res/Audio/background.mp3", true);
	m_JumpSound = new Audio("../PrettyEngine/src/game/res/Audio/jumpFX2.mp3", false);
	Application::Get().SetGameVisibility(&m_Visible);

	m_BackgroundMusic->Play();

	/*Entity* e = new Entity();
	e->AddComponent(audio);

	m_Scene->Add(e);*/

	m_Scene->Submit();
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate()
{

	
	
	//m_Visible = !Application::Get().EditorInUse();
	
	
	
	if (m_Player1Transform && m_GameHasStarted)
	{
		transformData.position = m_Player1Transform->position;
		if (m_Player1Transform->position.y > 100) {
			m_Winner = m_Player1->tag;
		 }
	}
	if (m_Player2Transform && m_GameHasStarted)
	{
		m_Player2Transform->position = m_Client->ReceivedTransformData().position;
		if (m_Player2Transform->position.y > 100) {
			m_Winner = m_Player2->tag;
		 }
	}
	if (m_Client != nullptr)
	{
		m_Client->SendData(&levelInfo, sizeof(LevelInfo));
		m_Client->SendData(&transformData, sizeof(TransformData));	
	}
//	if (serverShow)
		m_Scene->RenderScene();

		if (m_Winner != "None")
		{
			showEndGame = true;
			showStartGame = false;
		}
}

void GameLayer::OnImGuiRender()
	{
		static bool show = true;
		//ImGui::ShowDemoWindow(&show);
		StartTab(&show);
		//PeerConnectionTab(&show);
		MenuTab(&showMenu);
		LobbyTab(&showLobby);
		GameFinishedTab(&showEndGame);
		GameStartedTab(&showStartGame);
	}

void GameLayer::OnEvent(Event & event)
{
	EventHandler handler(event);
	handler.Handle<KeyPressedEvent>(BIND_EVENT_FN(GameLayer::OnKeyPressed));
	if (m_GameHasStarted)
	{
		handler.Handle<JumpEvent>(BIND_EVENT_FN(GameLayer::OnJump));
		handler.Handle<MoveEvent>(BIND_EVENT_FN(GameLayer::OnMove));
	}
	m_Scene->OnEvent(event);
}

bool GameLayer::OnJump(JumpEvent & e)
{
	if (m_Player1RB)
		m_Player1RB->ApplyForce(Vector2(0.0f, 10.0f));
	m_JumpSound->Play();
	return true;

}

bool GameLayer::OnMove(MoveEvent & e)
{
	if (e.GetDirection() == 1)
	{
		m_Player1RB->SetLinearVeclocity(Vector2(20, 0));

	}
	if (e.GetDirection() == -1)
	{
		m_Player1RB->SetLinearVeclocity(Vector2(-20, 0));
	}
	return true;
}

bool GameLayer::OnKeyPressed(KeyPressedEvent & e)
{
	if (e.GetKeyCode() == keyCode::Tab)
	{
		showMenu = showMenu ? false : true;
	}
	return true;
}

void GameLayer::StartTab(bool * show)
{
	
	static bool showPeerWindow = false;
	if (*show) {
		if (!ImGui::Begin("Start"))
		{
			ImGui::End();
			return;
		}

	

		ImGui::Text("Super Awsome Game");
		ImGui::Separator();
		ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
		if (ImGui::Button("Dedicated Server", ImVec2(ImGui::GetWindowWidth(), 0.0f)))
		{
			serverShow = true;
			m_Client = new Client(true);

			*show = false;
		}

		if (ImGui::Button("Join Server"))
		{
			clientShow = true;
			m_Client = new Client(false);
			*show = false;
		}
		ImGui::SameLine(); ImGui::InputText("Your Name", &levelInfo.playerName);
		
		ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();

		if (ImGui::Button("Peer to peer", ImVec2(ImGui::GetWindowWidth(), 0.0f)))
		{
			showPeerWindow = true;
			*show = false;
		}

		
		ImGui::End();
	}
	ClientLobbyTab(&clientShow);
	DedicatedServerTab(&serverShow);
	PeerConnectionTab(&showPeerWindow);
}

void GameLayer::PeerConnectionTab(bool* show)
{
	if (*show) {
		if (!ImGui::Begin("Start"))
		{
			ImGui::End();
			return;
		}

		ImGui::Text("Peer to peer connected game.");
		//ImGui::ProgressBar(0.1f);
		ImGui::Separator();

		ImGui::InputText("Your Name", &levelInfo.playerName);

		if (ImGui::Button("Create Room")) 
		{
			m_Client = new Client(true);
			//m_Client->SetLevelData(levelInfo);
			showLobby = true;
			*show = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Join Room"))
		{
			m_Client = new Client(false);
			//m_Client->SetLevelData(levelInfo);
			showLobby = true;
			*show = false;
		}

		
		ImGui::End();
	}
}

void GameLayer::DedicatedServerTab(bool* show)
{
	if (*show)
	{
		if (!ImGui::Begin("Start"))
		{
			ImGui::End();
			return;
		}

		if (!m_Client) {
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "ERROR: Server failed to initialise!");
		}
		else
		{
			levelInfo = m_Client->ReceivedLevelData();
			transformData = m_Client->ReceivedTransformData();
		
			ImGui::Text("You're a dedicated server now! Enjoy!");
			ImGui::Text("You can still press tab and use the level editor.");

			levelInfo.isFromHost = true;
			transformData.isFromHost = true;
			ImGui::Text("Select Level: "); ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 1, 0, 1), file.c_str());
			ImGui::SameLine();
			if (ImGui::Button("..."))
			{

				file = OpenFileDialog();
				//SetCharFromString(file, levelInfo.level);

			}

			if (file != "NULL")
			{
				for (int i = 0; i < sizeof(levelInfo.level) / sizeof(levelInfo.level[0]); i++)
				{
					if (file.size() > i) {
						levelInfo.level[i] = file[i];
					}
					else {
						levelInfo.level[i] = NULL;
					}
				}
			}
		}
		ImGui::End();
	}
}

void GameLayer::MenuTab(bool* show)
{
	if (*show) {
		if (!ImGui::Begin("Menu"))
		{
			ImGui::End();
			return;
		}

		if (ImGui::Button("Open Profiler")) 
		{
			showProfiler = true;
		}
		if (ImGui::Button("Editor Mode")) 
		{
			Application::Get().UseEditor(true);
			*show = false;
		}

		ImGui::End();

		Application::Get().GetEditor()->ProfilerTab(&showProfiler);
	}
}

void GameLayer::LobbyTab(bool* show)
{
	if (*show) {
		if (!ImGui::Begin("Start"))
		{
			ImGui::End();
			return;
		}

	

		ImGui::Text("Lobby");
		ImGui::Separator();

		//if(Host) Choose level.
		if (m_Client)
		{
			String otherPlayerName = "None";
			
			


			if (m_Client->IsHost())
			{
				levelInfo.isFromHost = true;
				transformData.isFromHost = true;
				ImGui::Text("Select level: "); ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 1, 0, 1), levelInfo.level);
				ImGui::SameLine();
				if (ImGui::Button("..."))
				{

					String file = OpenFileDialog();
					//SetCharFromString(file, levelInfo.level);

					for (int i = 0; i < sizeof(levelInfo.level) / sizeof(levelInfo.level[0]); i++)
					{
						if (file.size() > i) {
							levelInfo.level[i] = file[i];
						}
						else {
							levelInfo.level[i] = NULL;
						}
					}
				}
			}
			else
			{
				
				levelInfo.isFromHost = false;
				transformData.isFromHost = false;
				ImGui::Text("Level Selected: "); ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 1, 0, 1), m_Client->ReceivedLevelData().level);
			//	m_Client->SetLevelData(levelInfo);
			}
	
		//	ImGui::LabelText(levelInfo.playerName.c_str(),"OK");
			ImGui::Button(levelInfo.playerName.c_str()/*, ImVec2(ImGui::GetWindowWidth(), 0.0f)*/);
			const char* characters[] = { "Ahsoka", "Cyborg" };
			//static int selectedCharacter = 0;
			ImGui::SameLine(); ImGui::Combo("Select a Character", &levelInfo.selectedCharacter, characters, IM_ARRAYSIZE(characters));
			String charFile = levelInfo.selectedCharacter ? "../PrettyEngine/src/game/res/Models/cyborg/cyborg.obj" : "../PrettyEngine/src/game/res/Models/ahsoka/AhsokaTest1.obj";

			
			for (int i = 0; i < sizeof(levelInfo.characterPath) / sizeof(levelInfo.characterPath[0]); i++)
			{
				if (charFile.size() > i) {
					levelInfo.characterPath[i] = charFile[i];
					//destination++;
				}
				else {
					levelInfo.characterPath[i] = NULL;
					//destination++;
				}
			}

			if (m_Client->m_PlayerConnected)
			{
				otherPlayerName = m_Client->ReceivedLevelData().playerName;
			
				ImGui::Button(otherPlayerName.c_str());
			
				ImGui::SameLine(); ImGui::Text(characters[m_Client->ReceivedLevelData().selectedCharacter]);
				ImGui::Spacing(); ImGui::Spacing();  ImGui::Spacing(); ImGui::Spacing();
				if (ImGui::Button("Ready"))
				{
					levelInfo.playerReady = true;
					m_Client->SetLevelData(levelInfo);
					
				}
				if (levelInfo.playerReady)
				{
					ImGui::TextColored(ImVec4(0, 1, 0, 1), "OK");
					if (m_Client->ReceivedLevelData().playerReady && !m_GameHasStarted)
					{
						if (levelInfo.level != "NULL")
						{
							ImGui::TextColored(ImVec4(0, 1, 1, 1), "Loading...");
							m_Scene = LevelManager::Import(m_Client->IsHost() ? levelInfo.level : m_Client->ReceivedLevelData().level);
							m_Player1 = m_Scene->GetEntityByTag("Player1");
							if (m_Player1)
							{
								m_Player1Transform = m_Player1->GetComponent<Transform>();
								ModelComponent* model1 = m_Player1->GetComponent<ModelComponent>();
								if (model1)
								{
									m_Player1->RemoveComponent(model1);
									delete model1;
									ModelComponent* newModel = new ModelComponent(new Model(levelInfo.characterPath));
									m_Player1->AddComponent(newModel);
									m_Player1RB = m_Player1->GetComponent<Rigidbody>();
									
								}
							}
							m_Player2 = m_Scene->GetEntityByTag("Player2");
							if (m_Player2)
							{
								m_Player2Transform = m_Player2->GetComponent<Transform>();
								
								ModelComponent* model2 = m_Player2->GetComponent<ModelComponent>();
								if (model2)
								{
									m_Player2->RemoveComponent(model2);
									delete model2;
									ModelComponent* newModel = new ModelComponent(new Model(m_Client->ReceivedLevelData().characterPath));
									m_Player2->AddComponent(newModel);
								

								}
							//	Rigidbody* rb = m_Player2->GetComponent<Rigidbody>();
							//	m_Player2->RemoveComponent(rb);
							//	delete rb;
							//	rb = nullptr;
							}
							m_Scene->Submit();

							showStartGame = true;

						}
						else
						{
							ImGui::TextColored(ImVec4(1, 0, 0, 1), "Please Select a level");
						}
						m_GameHasStarted = true;
						
					}
					
					
				}
				

			}
			else
			{
				ImGui::Spacing(); ImGui::Spacing();  ImGui::Spacing(); ImGui::Spacing();
				ImGui::Text("Waiting for the other player to connect");
			}


			if (m_GameHasStarted)
				*show = false;
			//if(player2Connected) show Start button else show waiting text

			//ImGui::SameLine();
			//if (ImGui::Button("Start Game"))
			//{
			//	*show = false;
			//}
		}
		ImGui::End();

	}
}

void GameLayer::ClientLobbyTab(bool * show)
{

	if (*show) {
		if (!ImGui::Begin("Start"))
		{
			ImGui::End();
			return;
		}


		ImGui::Text("Lobby");
		ImGui::Separator();

		//if(Host) Choose level.
		if (m_Client)
		{
			String otherPlayerName = "None";


			if (m_Client->GetID() != -1)
			{
				levelInfo.clientID = m_Client->GetID();
				transformData.clientID = m_Client->GetID();
			}
			levelInfo.isFromHost = false;
			transformData.isFromHost = false;






			ImGui::Text("Level Selected: "); ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 1, 0, 1), m_Client->ReceivedLevelData().level);

			ImGui::Button(levelInfo.playerName.c_str());
			const char* characters[] = { "Ahsoka", "Cyborg" };

			ImGui::SameLine(); ImGui::Combo("Select a Character", &levelInfo.selectedCharacter, characters, IM_ARRAYSIZE(characters));
			String charFile = levelInfo.selectedCharacter ? "../PrettyEngine/src/game/res/Models/cyborg/cyborg.obj" : "../PrettyEngine/src/game/res/Models/ahsoka/AhsokaTest1.obj";


			for (int i = 0; i < sizeof(levelInfo.characterPath) / sizeof(levelInfo.characterPath[0]); i++)
			{
				if (charFile.size() > i) {
					levelInfo.characterPath[i] = charFile[i];

				}
				else {
					levelInfo.characterPath[i] = NULL;

				}
			}

			if (/*m_Client->ReceivedLevelData().clientID != m_Client->GetID() &&*/ m_Client->ReceivedLevelData().clientID != -1)
			{
				otherPlayerName = m_Client->ReceivedLevelData().playerName;

				ImGui::Button(otherPlayerName.c_str());

				ImGui::SameLine(); ImGui::Text(characters[m_Client->ReceivedLevelData().selectedCharacter]);
				ImGui::Spacing(); ImGui::Spacing();  ImGui::Spacing(); ImGui::Spacing();
				if (ImGui::Button("Ready"))
				{
					levelInfo.playerReady = true;
					m_Client->SetLevelData(levelInfo);

				}
				if (levelInfo.playerReady)
				{
					ImGui::TextColored(ImVec4(0, 1, 0, 1), "OK");
					if (m_Client->ReceivedLevelData().playerReady && !m_GameHasStarted)
					{
						if (levelInfo.level != "NULL")
						{
							ImGui::TextColored(ImVec4(0, 1, 1, 1), "Loading...");
							m_Scene = LevelManager::Import(m_Client->IsHost() ? levelInfo.level : m_Client->ReceivedLevelData().level);
							m_Player1 = m_Scene->GetEntityByTag("Player1");
							if (m_Player1)
							{
								m_Player1Transform = m_Player1->GetComponent<Transform>();
								ModelComponent* model1 = m_Player1->GetComponent<ModelComponent>();
								if (model1)
								{
									m_Player1->RemoveComponent(model1);
									delete model1;
									ModelComponent* newModel = new ModelComponent(new Model(levelInfo.characterPath));
									m_Player1->AddComponent(newModel);
									m_Player1RB = m_Player1->GetComponent<Rigidbody>();

								}
							}
							m_Player2 = m_Scene->GetEntityByTag("Player2");
							if (m_Player2)
							{
								m_Player2Transform = m_Player2->GetComponent<Transform>();

								ModelComponent* model2 = m_Player2->GetComponent<ModelComponent>();
								if (model2)
								{
									m_Player2->RemoveComponent(model2);
									delete model2;
									ModelComponent* newModel = new ModelComponent(new Model(m_Client->ReceivedLevelData().characterPath));
									m_Player2->AddComponent(newModel);


								}
							}
							m_Scene->Submit();
							showStartGame = true;
						}
						else
						{
							ImGui::TextColored(ImVec4(1, 0, 0, 1), "Please Select a level");
						}
						m_GameHasStarted = true;

					}


				}


			}
			else
			{
				ImGui::Spacing(); ImGui::Spacing();  ImGui::Spacing(); ImGui::Spacing();
				ImGui::Text("Waiting for the other player to connect");
			}


			if (m_GameHasStarted)
				*show = false;
		}
		ImGui::End();

	}
}

static bool set = false;

void GameLayer::GameFinishedTab(bool* show)
{
	if (*show) 
	{
		if(!ImGui::Begin("End Game"))
		{
			ImGui::End();
			return;
		}
		m_GameHasStarted = false;
		if (!set) {
			levelInfo.playerReady = false;
			set = true;
		}
		
		m_Client->SetLevelData(levelInfo);
		if (m_Winner == m_Player1->tag)
		{
			ImGui::Text(levelInfo.playerName.c_str()); ImGui::SameLine(); ImGui::Text("Won !!");
		}
		else if (m_Winner == m_Player2->tag)
		{
			ImGui::Text(m_Client->ReceivedLevelData().playerName.c_str()); ImGui::SameLine(); ImGui::Text("Won !!");
		}

			if (ImGui::Button("Start a new level"))
				{
					levelInfo.playerReady = true;
					m_Client->SetLevelData(levelInfo);

				}
			if (levelInfo.playerReady)
				{
					ImGui::TextColored(ImVec4(0, 1, 0, 1), "OK");
					if (m_Client->ReceivedLevelData().playerReady)
					{
							ImGui::TextColored(ImVec4(0, 1, 1, 1), "Loading...");
							m_Scene = LevelManager::Import("../PrettyEngine/src/game/res/Levels/Level2.xml");
							m_Player1 = m_Scene->GetEntityByTag("Player1");
							if (m_Player1)
							{
								m_Player1Transform = m_Player1->GetComponent<Transform>();
								ModelComponent* model1 = m_Player1->GetComponent<ModelComponent>();
								if (model1)
								{
									m_Player1->RemoveComponent(model1);
									delete model1;
									ModelComponent* newModel = new ModelComponent(new Model(levelInfo.characterPath));
									m_Player1->AddComponent(newModel);
									m_Player1RB = m_Player1->GetComponent<Rigidbody>();

								}
							}
							m_Player2 = m_Scene->GetEntityByTag("Player2");
							if (m_Player2)
							{
								m_Player2Transform = m_Player2->GetComponent<Transform>();

								ModelComponent* model2 = m_Player2->GetComponent<ModelComponent>();
								if (model2)
								{
									m_Player2->RemoveComponent(model2);
									delete model2;
									ModelComponent* newModel = new ModelComponent(new Model(m_Client->ReceivedLevelData().characterPath));
									m_Player2->AddComponent(newModel);


								}
							}
							m_Scene->Submit();
							showStartGame = true;
							set = false;
					
						m_GameHasStarted = true;

					}


				}

		ImGui::End();
	}
}
void GameLayer::GameStartedTab(bool* show)
{
	if (*show) 
	{
		if(!ImGui::Begin("Start Game", show))
		{
			ImGui::End();
			return;
		}
		
		ImGui::Text("The game has started! \n\n Controls: W - Jump | A - Move left | D - Move right \n\n Press Tab for MainMenu \n\n Press Esc to Quit the game. \n\n Camera Controls - Alt + Left | Alt + Middle Button | Scroll \n\n You can move or close this window any time. \n\n Mission: That's for you to find out! ");

		ImGui::End();
	}
}
