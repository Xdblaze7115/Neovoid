#ifdef NEO_PLATFORM_WINDOWS
#include <Windows.h>
#endif
#include "Win32Window.hpp"
#include "WindowsInput.hpp"

namespace WindowsInput {
	Vector2 m_LastMousePosition = Vector2(0.0f, 0.0f);

	bool IsKeyPressed(int keycode) {
		auto window = static_cast<HWND>(Win32Window::GetNativeWindow());
		if (GetForegroundWindow() != window) {
			return false;
		}
		return (GetAsyncKeyState(keycode) & 0x8000) != 0; // 0x8000 Means Being Pressed
	}

	bool IsMouseButtonPressed(int button) {
		auto window = static_cast<HWND>(Win32Window::GetNativeWindow());
		if (GetForegroundWindow() != window) {
			return false;
		}

		switch (button) {
		case 0: button = VK_LBUTTON; break;
		case 1: button = VK_RBUTTON; break;
		case 2: button = VK_MBUTTON; break;
		case 3: button = VK_XBUTTON1; break;
		case 4: button = VK_XBUTTON2; break;
		default: return false;
		}
		return (GetAsyncKeyState(button) & 0x8000) != 0;
	}

	Vector2 GetMousePosition() {
		auto window = static_cast<HWND>(Win32Window::GetNativeWindow());
		if (!IsWindow(window)) {
			return m_LastMousePosition;
		}

		POINT point;
		if (!GetCursorPos(&point)) {
			return m_LastMousePosition;
		}

		if (!ScreenToClient(window, &point)) {
			return m_LastMousePosition;
		}

		RECT client_area;
		GetClientRect(window, &client_area);

		if (!PtInRect(&client_area, point)) {
			return m_LastMousePosition;
		}

		m_LastMousePosition = Vector2((float)point.x, (float)point.y);
		return Vector2((float)point.x, (float)point.y);
	}
}