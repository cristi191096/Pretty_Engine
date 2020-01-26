#pragma once

#include "Event.h"

namespace PrettyEngine {

	class PE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(double x, double y) : m_MouseX(x), m_MouseY(y) {}

		inline double GetX() const { return m_MouseX; }
		inline double GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		double m_MouseX, m_MouseY;
	};

	class PE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(double xoffset, double yoffset) : m_XOffset(xoffset), m_YOffset(yoffset) {}

		inline double GetXOffset() const { return m_XOffset; }
		inline double GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		double m_XOffset, m_YOffset;
	};

	class PE_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton | EventCategoryInput)

	protected:
		MouseButtonEvent(int button) : m_Button(button) {}

		int m_Button;
	};

	class PE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << GetName() << ": " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class PE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << GetName() << ": " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}
