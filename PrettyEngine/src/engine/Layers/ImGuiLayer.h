#pragma once

#include "engine\Core\Layer.h"
#include "engine\Core\Core.h"

#include "engine\Events\Event.h"
#include "engine\Events\ApplicationEvent.h"
#include "engine\Events\MouseEvent.h"
#include "engine\Events\KeyEvent.h"

namespace PrettyEngine {

	class PE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;

	};
}