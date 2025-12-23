#pragma once
#include "Event.hpp"

class WindowResizeEvent : public Event {
private:
	int m_Width, m_Height;
public:
	WindowResizeEvent(int width, int height) :
		Event(EventCategory::Application, EventType::WindowResize),
		m_Width(width), m_Height(height)
	{}

	static EventType GetStaticType() {
		return EventType::WindowResize;
	}

	std::string ToString() const override {
		return std::format("Window Resize Event -> {}, {}", m_Width, m_Height);
	}

	int GetWidth() {
		return m_Width;
	}

	int GetHeight() {
		return m_Height;
	}
};

class WindowCloseEvent : public Event {
public:
	WindowCloseEvent() :
		Event(EventCategory::Application, EventType::WindowClose)
	{}

	static EventType GetStaticType() {
		return EventType::WindowClose;
	}

	std::string ToString() const override {
		return std::format("Window Close Event");
	}
};

class AppTickEvent : public Event {
public:
	AppTickEvent() :
		Event(EventCategory::Application, EventType::AppTick)
	{}

	static EventType GetStaticType() {
		return EventType::AppTick;
	}

	std::string ToString() const override {
		return std::format("App Tick Event");
	}
};

class AppUpdateEvent : public Event {
public:
	AppUpdateEvent() :
		Event(EventCategory::Application, EventType::AppUpdate)
	{}

	static EventType GetStaticType() {
		return EventType::AppUpdate;
	}

	std::string ToString() const override {
		return std::format("App Update Event");
	}
};

class AppRenderEvent : public Event {
public:
	AppRenderEvent() :
		Event(EventCategory::Application, EventType::AppRender)
	{}

	static EventType GetStaticType() {
		return EventType::AppRender;
	}

	std::string ToString() const override {
		return std::format("App Render Event");
	}
};