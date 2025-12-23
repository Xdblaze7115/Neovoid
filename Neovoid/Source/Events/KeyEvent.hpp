#pragma once
#include "Event.hpp"

class KeyEvent : public Event {
protected:
	unsigned int m_KeyCode;
public:
	KeyEvent(EventType type, unsigned int keycode) :
		Event(EventCategory::Keyboard, type),
		m_KeyCode(keycode)
	{}

	unsigned int GetKeyCode() {
		return m_KeyCode;
	}
};

class KeyPressedEvent : public KeyEvent {
private:
	int m_RepeatCount;
public:
	KeyPressedEvent(unsigned int keycode, int repeat_count) :
		KeyEvent(EventType::KeyPressed, keycode),
		m_RepeatCount(repeat_count) {
	}

	static EventType GetStaticType() {
		return EventType::KeyPressed;
	}

	std::string ToString() const override {
		return std::format("Key Pressed Event -> {} Repeats -> {}", m_KeyCode, m_RepeatCount);
	}

	int GetRepeatCount() {
		return m_RepeatCount;
	}
};

class KeyReleasedEvent : public KeyEvent {
public:
	KeyReleasedEvent(unsigned int keycode) :
		KeyEvent(EventType::KeyReleased, keycode)
	{}

	static EventType GetStaticType() {
		return EventType::KeyReleased;
	}

	std::string ToString() const override {
		return std::format("Key Released Event -> {}", m_KeyCode);
	}
};

class KeyTypedEvent : public KeyEvent {
public:
	KeyTypedEvent(unsigned int keycode) :
		KeyEvent(EventType::KeyTyped, keycode)
	{}

	static EventType GetStaticType() {
		return EventType::KeyTyped;
	}

	std::string ToString() const override {
		return std::format("Key Typed Event -> {}", m_KeyCode);
	}
};