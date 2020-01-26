#pragma once
#include "engine\Core\Core.h"
#include <fmod.hpp>


namespace PrettyEngine {

	class AudioClip;

	class PE_API AudioChannel
	{
	public:
		float m_Frequency;
		int m_Priority;
	public:
		AudioChannel();
		AudioChannel(const String& file, bool loop = false, const float& frequency = 16400.0f, const int& priority = 0);
		~AudioChannel();

		void SetDefaults(const float& frequency, const int& priority);

		void Play(bool paused = false);

	private:
		
		FMOD::Channel* m_Channel = NULL;
		AudioClip* m_Sound;
	};

}