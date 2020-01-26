#include "pepch.h"
#include "AudioChannel.h"
#include "AudioClip.h"
#include "AudioContext.h"

namespace PrettyEngine {
	AudioChannel::AudioChannel()
	{
	}
	AudioChannel::AudioChannel(const String& file, bool loop, const float& frequency, const int& priority)
		: m_Frequency(frequency), m_Priority(priority)
	{
		m_Sound = new AudioClip(file, loop);
		m_Sound->m_FMODSound->setDefaults(frequency, priority);
	}

	AudioChannel::~AudioChannel()
	{
		
		
	}

	void AudioChannel::SetDefaults(const float & frequency, const int & priority)
	{
		m_Sound->m_FMODSound->setDefaults(frequency, priority);
	}

	void AudioChannel::Play(bool paused )
	{
		AudioContext::Get()->m_LLSystem->playSound(m_Sound->m_FMODSound, NULL, paused, &m_Channel);
	}

}
