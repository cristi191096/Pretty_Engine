#include "pepch.h"
#include "AudioContext.h"


namespace PrettyEngine {

	AudioContext* AudioContext::s_Instance = nullptr;

	void AudioContext::Create()
	{
		s_Instance = new AudioContext();
	}

	void AudioContext::Update()
	{
		m_HLSystem->update();
	}

	void AudioContext::Destroy() const
	{
	}

	AudioContext::AudioContext()
	{
		FMOD_RESULT result;
		result = FMOD::Studio::System::create(&m_HLSystem);
		m_HLSystem->getLowLevelSystem(&m_LLSystem);

		if (result != FMOD_OK)
		{
			PE_ERROR("FMOD error! {0}", result);

		}

		m_LLSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
		result = m_HLSystem->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL);

		if (result != FMOD_OK)
		{
			PE_ERROR("FMOD initialising error! {0}", result);

		}
	}

	AudioContext::~AudioContext()
	{
		m_LLSystem->release();
		m_HLSystem->unloadAll();
		m_HLSystem->release();
	}

}