#pragma once
#include "engine\Core\Core.h"
#include "AudioClip.h"
#include "AudioChannel.h"

#include <fmod.hpp>
#include <fmod_studio.hpp>


namespace PrettyEngine {


	class PE_API AudioContext {

	public:

		static void Create();

		inline static AudioContext* Get() { return s_Instance; }

		void Update();

		void Destroy() const;

	private:
		static AudioContext* s_Instance;
		AudioContext();
		~AudioContext();

	private:
		FMOD::Studio::System* m_HLSystem = NULL;
		FMOD::System* m_LLSystem = NULL;

		friend AudioClip;
		friend AudioChannel;
	};
}