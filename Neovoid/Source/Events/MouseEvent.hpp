#pragma once
#include "Event.hpp"

class MouseMovedEvent : public Event {
private:
	float m_Mouse_X, m_Mouse_Y;
public:
	MouseMovedEvent(float x, float y) :
		Event(EventCategory::Mouse, EventType::MouseMoved),
		m_Mouse_X(x), m_Mouse_Y(y)
	{}

	static EventType GetStaticType() {
		return EventType::MouseMoved;
	}

	std::string ToString() const override {
		return std::format("Mouse Moved Event -> {}, {}", m_Mouse_X, m_Mouse_Y);
	}

	float GetX() {
		return m_Mouse_X;
	}

	float GetY() {
		return m_Mouse_Y;
	}
};

class MouseScrolledEvent : public Event {
private:
	float m_X_Offset, m_Y_Offset;
public:
	MouseScrolledEvent(float x_offset, float y_offset) :
		Event(EventCategory::Mouse, EventType::MouseScrolled),
		m_X_Offset(x_offset), m_Y_Offset(y_offset)
	{}

	static EventType GetStaticType() {
		return EventType::MouseScrolled;
	}

	std::string ToString() const override {
		return std::format("Mouse Scrolled Event -> {}, {}", m_X_Offset, m_Y_Offset);
	}

	float GetXOffset() {
		return m_X_Offset;
	}

	float GetYOffset() {
		return m_Y_Offset;
	}
};

class MouseButtonEvent : public Event {
protected:
	int m_Button;
public:
	MouseButtonEvent(EventType type, int button) :
		Event(EventCategory::Mouse, type),
		m_Button(button)
	{}

	int GetMouseButton() {
		return m_Button;
	}
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
	MouseButtonPressedEvent(int button) :
		MouseButtonEvent(EventType::MouseButtonPressed, button)
	{}

	static EventType GetStaticType() {
		return EventType::MouseButtonPressed;
	}

	std::string ToString() const override {
		return std::format("Mouse Button Pressed Event -> {}", m_Button);
	}
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
	MouseButtonReleasedEvent(int button) :
		MouseButtonEvent(EventType::MouseButtonReleased, button)
	{}

	static EventType GetStaticType() {
		return EventType::MouseButtonReleased;
	}

	std::string ToString() const override {
		return std::format("Mouse Button Released Event -> {}", m_Button);
	}
};