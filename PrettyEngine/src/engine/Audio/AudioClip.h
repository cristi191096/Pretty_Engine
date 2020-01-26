#pragma once
#include "engine\Core\Core.h"
#include "AudioChannel.h"
#include <fmod.hpp>

namespace PrettyEngine
{
	class PE_API AudioClip
	{
	public:
		AudioClip(const String& file, bool loop = false);
		~AudioClip();

		inline const String& GetPath() const { return m_FilePath; }
		inline void SetPath(const String& path) { m_FilePath = path; }

	private:
		String m_FilePath;
		FMOD::Sound* m_FMODSound = NULL;

		friend AudioChannel;
	};
}