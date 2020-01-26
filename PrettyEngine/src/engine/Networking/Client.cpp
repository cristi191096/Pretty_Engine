#include "pepch.h"
#include "Client.h"

namespace PrettyEngine
{
	Client::Client(bool isHost)
		: m_IsHost(isHost)
	{
	
		if (isHost)
		{
			m_Address.host = ENET_HOST_ANY;
			m_Address.port = 1234;

			m_Host = enet_host_create(&m_Address, 32, 2, 0, 0);

			if (m_Host == NULL)
				PE_ERROR("Host could not be initialised!");
		}
		else
		{
			m_Host = enet_host_create(NULL, 1, 2, 0, 0);

			if (m_Host == NULL)
				PE_ERROR("Host could not be initialised!");

			enet_address_set_host(&m_Address, "localhost");
			m_Address.port = 1234;

			m_Peer = enet_host_connect(m_Host, &m_Address, 2, 0);

			if (m_Peer == NULL)
				PE_ERROR("No available peers for initializing an ENet connection!");

		}
	}

	Client::~Client()
	{
	}

	void Client::SendData(void* data, size_t size)
	{
		if (!m_IsHost)
		{
			m_PlayerConnected = true;
			m_Data = enet_packet_create(data, size, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(m_Peer, 0, m_Data);
		}
		else
		{
			m_Data = enet_packet_create(data, size, ENET_PACKET_FLAG_RELIABLE);
			enet_host_broadcast(m_Host, 0, m_Data);
		}
		while (enet_host_service(m_Host, &m_Event, 0) > 0)
		{
			if (m_IsHost)
			{
				//String data = "someClient";
				int packetType = 0;
				switch (m_Event.type)
				{
				case ENET_EVENT_TYPE_CONNECT:
					m_PlayerConnected = true;
					m_ConnectedClients++;
					id = enet_packet_create(&m_ConnectedClients, sizeof(int), ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(m_Event.peer, 0, id);
					break;

				case ENET_EVENT_TYPE_RECEIVE:
					
					if (m_Event.packet && m_Event.packet->data)
						memcpy(&packetType, m_Event.packet->data, sizeof(int));
					if (packetType == PacketType::LEVELINFO) 
					{
						LevelInfo* tempInfo = new LevelInfo;
						memcpy(tempInfo, m_Event.packet->data, sizeof(LevelInfo));
						if (!tempInfo->isFromHost) {
							memcpy(&m_LevelData, m_Event.packet->data, sizeof(LevelInfo));
							
						}
					}
					if (packetType == PacketType::TRANSFORM)
					{
						TransformData* tempTransform = new TransformData;
						memcpy(tempTransform, m_Event.packet->data, sizeof(TransformData));
						if (!tempTransform->isFromHost)
						{
							memcpy(&m_TransformData, m_Event.packet->data, sizeof(TransformData));
						}
					}
					break;

				default:
					break;
				}
			}
			else
			{
				int packetType = 0;
				//m_PlayerConnected = true;
				//enet_peer_send(m_Peer, 0, m_Data);
				switch (m_Event.type)
				{
				case ENET_EVENT_TYPE_CONNECT:
					break;

				case ENET_EVENT_TYPE_RECEIVE:
					if (m_Event.packet && m_Event.packet->dataLength == sizeof(int)) {
						memcpy(&m_ClientID, m_Event.packet->data, sizeof(int));
						
					}
						

					if (m_Event.packet  && m_Event.packet->data)
						memcpy(&packetType, m_Event.packet->data, sizeof(int));
					if (packetType == PacketType::LEVELINFO)
					{

						LevelInfo* tempInfo = new LevelInfo;
						memcpy(tempInfo, m_Event.packet->data, sizeof(LevelInfo));
					
						if (tempInfo->isFromHost && tempInfo->clientID != m_ClientID) {
							memcpy(&m_LevelData, m_Event.packet->data, sizeof(LevelInfo));
						}
					}
					if (packetType == PacketType::TRANSFORM)
					{
						TransformData* tempTransform = new TransformData;
						memcpy(tempTransform, m_Event.packet->data, sizeof(TransformData));
						if (tempTransform->isFromHost && tempTransform->clientID != m_ClientID)
							memcpy(&m_TransformData, m_Event.packet->data, sizeof(TransformData));
					}

					break;
					
				default:
					break;
				}
			}
		}

		
	}

}

