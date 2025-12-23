#pragma once
#include <string>
#include <format>
#include <functional>
#include <magic_enum.hpp>

#define NEO_BIND_CLASS_FUNC(x) std::bind(&x, this, std::placeholders::_1)
#define NEO_BIND_STATIC_FUNC(x) std::bind(&x, std::placeholders::_1)
#define NEO_BIND_FUNCTION(x) std::bind(x, std::placeholders::_1)

enum class EventCategory {
	Application,
	Input,
	Keyboard,
	Mouse,
	MouseButton
};

enum class EventType {
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
};

class Event {
	friend class EventDispatcher;
private:
	EventCategory m_EventCategory;
	EventType m_EventType;
public:
	Event(EventCategory event_category, EventType event_type) :
		m_EventCategory(event_category),
		m_EventType(event_type)
	{}

	bool Handled = false;

	EventCategory GetEventCategory() {
		return m_EventCategory;
	}

	EventType GetEventType() {
		return m_EventType;
	}

	const char* GetName() {
		return magic_enum::enum_name(m_EventType).data();
	}

	virtual std::string ToString() const {
		return std::string(magic_enum::enum_name(m_EventType));
	}
};

class EventDispatcher {
	template<typename T>
	using EventFn = std::function<bool(T&)>;
private:
	Event& m_Event;
public:
	EventDispatcher(Event& event) :
		m_Event(event)
	{}

	template<typename T>
	bool Dispatch(EventFn<T> func) {
		if (m_Event.GetEventType() == T::GetStaticType()) {
			m_Event.Handled = func(*(T*)&m_Event);
			return true;
		}
		return false;
	}
};