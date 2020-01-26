#pragma once
#include "engine\Core\Core.h"
#include "engine\ECS\Components\TransformComponent.h"
#include <enet\enet.h>

namespace PrettyEngine
{
	struct LevelInfo 
	{
		int packetType = 2;
		int clientID = -1;
		int selectedCharacter = 0;
		bool isFromHost = false;
		bool playerReady = false;
		String playerName;
		char level[1024] = "NULL";
		char characterPath[1024] = "NULL";
	//	char levelAAAA[1024];
	};

	struct TransformData
	{
		int packetType = 1;
		int clientID = -1;
		bool isFromHost = false;
		Vector3 position;
	};

	class PE_API Client
	{
	public:
		enum PacketType
		{
			NONE = 0, TRANSFORM, LEVELINFO
		};

		bool m_PlayerConnected = false;
	public:
		Client(bool isHost = false);
		~Client();

		//inline void SetLevelData(void* data, size_t size) { m_Data = enet_packet_create(data, size, ENET_PACKET_FLAG_RELIABLE); }
		inline void SetLevelData(LevelInfo data) { m_Data = enet_packet_create(&data, sizeof(LevelInfo), ENET_PACKET_FLAG_RELIABLE); }
		//void SendData(void* data, size_t size);
	
		inline LevelInfo ReceivedLevelData() const {  return m_LevelData; }
		inline TransformData ReceivedTransformData() const { return m_TransformData; }
		inline int GetID() const { return m_ClientID; }

		void SendData(void* data, size_t size);
		bool IsHost() const { return m_IsHost; }

	private:
		bool m_IsHost;
		int m_ClientID = -1;
		int m_ConnectedClients = 0;
		LevelInfo m_LevelData;
		TransformData m_TransformData;
		ENetAddress m_Address;
		ENetHost* m_Host;
		ENetPeer* m_Peer;
		ENetEvent m_Event;
		ENetPacket* m_Data;
		ENetPacket* id;

	};
}