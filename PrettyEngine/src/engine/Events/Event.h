#pragma once

#include "pepch.h"
#include "engine\Core\Core.h"


namespace PrettyEngine {

	enum class EventType 
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender, Jump, Move, Attack, Block, 
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory 
	{
		None = 0,
		EventCategoryApplication	= BIT(0), 
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
		EventCategoryControl		= BIT(5)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class PE_API Event
	{
	public:
		bool Handeled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		
		inline bool IsInCategory(EventCategory category) 
		{
			return GetCategoryFlags() & category;
		}
	};

	class EventHandler
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventHandler(Event& event) : m_Event(event) {}

		template<typename T>
		bool Handle(EventFn<T> func) 
		{
			if(m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handeled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};
	
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
