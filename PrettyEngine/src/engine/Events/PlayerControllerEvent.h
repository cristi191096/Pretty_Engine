#pragma once

#include "Event.h"

namespace PrettyEngine
{

	enum KeyBinds {			// TODO: How Would I make that cusomisable
		Attack = 32,		//Space 
		MoveLeft = 65,		// A
		MoveRight = 68,		// D
		Jump = 87,			// W
		Block = 83			// S
	};


	class PE_API JumpEvent : public Event
	{
	public:

		JumpEvent() { }

		//inline int GetKeyCode() const { return m_KeyCode; }
		//inline void SetKeyCode(int keyCode) { m_KeyCode = keyCode; }


		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput | EventCategoryControl)
			EVENT_CLASS_TYPE(Jump)




			std::string ToString() const override
		{
			std::stringstream ss;
			ss << "JumpEvent: ";
			return ss.str();
		}

	private:
		//int m_KeyCode = 32;		// Space. List of keyCodes in GLInputCodes.h

	};

	class PE_API AttackEvent : public Event
	{
	public:

		AttackEvent() { }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput | EventCategoryControl)
		EVENT_CLASS_TYPE(Attack)




		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "AttackEvent: ";
			return ss.str();
		}

	};

	class PE_API BlockEvent : public Event
	{
	public:

		BlockEvent() { }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput | EventCategoryControl)
		EVENT_CLASS_TYPE(Block)




		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "BlockEvent: ";
			return ss.str();
		}


	};

	class PE_API MoveEvent : public Event
	{
	public:

		MoveEvent(int direction) : m_Direction(direction) { }

		inline int GetDirection() const { return m_Direction; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput | EventCategoryControl)
		EVENT_CLASS_TYPE(Move)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MoveEvent: " << (m_Direction > 0) ? "Right" : "Left";
			return ss.str();
		}

	private:
		int m_Direction;	// +1 or -1

	};


}

