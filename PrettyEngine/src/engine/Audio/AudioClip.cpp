#include "pepch.h"
#include "AudioClip.h"
#include "AudioContext.h"

namespace PrettyEngine
{

	AudioClip::AudioClip(const String& file, bool loop)
		: m_FilePath(file)
	{
		AudioContext::Get()->m_LLSystem->createSound(file.c_str(), loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF, NULL, &m_FMODSound);
	}

	AudioClip::~AudioClip()
	{
		
	}
}