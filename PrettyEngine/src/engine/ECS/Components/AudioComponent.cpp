#include "pepch.h"
#include "AudioComponent.h"

namespace PrettyEngine
{

	Audio::Audio(const String& file, bool loop, const float& frequency , const int& priority )
	{
		m_Channel = new AudioChannel(file, loop, frequency, priority);
	}

	Audio::~Audio()
	{
		
	}

	void Audio::Init()
	{
	}

}