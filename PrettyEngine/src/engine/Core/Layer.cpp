#include "pepch.h"
#include "Layer.h"

namespace PrettyEngine {

	Layer::Layer(const std::string & name)
		: m_DebugName(name), m_Visible(true)
	{
	}

	Layer::~Layer()
	{
	}
}