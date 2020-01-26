#include "pepch.h"
#include "NetworkContext.h"
#include <enet/enet.h>

namespace PrettyEngine 
{
	NetworkContext* NetworkContext::s_Instance = nullptr;

	void NetworkContext::Create()
	{
		s_Instance = new NetworkContext();
	}

	void NetworkContext::Update()
	{

	}

	void NetworkContext::Destroy() const
	{
	}

	NetworkContext::NetworkContext()
	{
		if (enet_initialize() != 0)
		{
			PE_ERROR("Network system failed to initialise!");
		}
	}

	NetworkContext::~NetworkContext()
	{
	}

}