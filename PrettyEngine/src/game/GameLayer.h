#pragma once
#include "PrettyEngine.h"
#include "engine\ECS\Components\Components.h"
#include "engine\Networking\Client.h"

using namespace PrettyEngine;



class GameLayer : public Layer
{

		public:
		GameLayer();
		~GameLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;
		virtual void OnImGuiRender() override;

	private:
		bool m_GameHasStarted = false;
		Client* m_Client = nullptr;
		Audio* m_BackgroundMusic;
		Audio* m_JumpSound;
		String m_PlayerName;
		String m_Player1Character;
		String m_Player2Character;
		Entity* m_Player1;
		Entity* m_Player2;
		Rigidbody* m_Player1RB;
		Transform* m_Player1Transform;
		Transform* m_Player2Transform;
		String m_Winner = "None"; 
		//Rigidbody* m_Player2;
	
		bool OnJump(JumpEvent& e);
		bool OnMove(MoveEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);

		void StartTab(bool* show);
		void PeerConnectionTab(bool* show);
		void DedicatedServerTab(bool* show);
		void MenuTab(bool* show);
		void LobbyTab(bool* show); 
		void ClientLobbyTab(bool* show); 
		void GameFinishedTab(bool* show);
		void GameStartedTab(bool* show);

};