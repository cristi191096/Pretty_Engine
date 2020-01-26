#pragma once
#include "Component.h"
#include "engine\Audio\AudioChannel.h"

namespace PrettyEngine {


	class Audio : public Component
	{

	public:


	public:
		Audio(const String& file, bool loop = false, const float& frequency = 16400.0f, const int& priority = 0);
		~Audio();

		virtual ComponentType GetType() const override { return GetStaticType(); }

		static ComponentType GetStaticType() {
			static ComponentType type = ComponentType::Audio;
			return type;
		}

		virtual void Init() override;

		inline void SetProperties(const float& frequency, const int& priority) { m_Channel->SetDefaults(frequency, priority); }
		inline void Play() { m_Channel->Play(false); }
		inline void Pause() { m_Channel->Play(true); }

	private:
		AudioChannel* m_Channel;
	};
}
