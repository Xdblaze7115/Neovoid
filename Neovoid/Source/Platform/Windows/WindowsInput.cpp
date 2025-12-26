#ifdef NEO_PLATFORM_WINDOWS
#include <Windows.h>
#endif
#include "Win32Window.hpp"
#include "WindowsInput.hpp"

namespace WindowsInput {
	bool m_MouseVisible = true;
	Vector2 m_LastMousePosition = Vector2(0.0f, 0.0f);

	void SetMousePosition(Vector2 position) {
		auto window = static_cast<HWND>(Win32Window::GetNativeWindow());
		if (!IsWindow(window)) {
			return;
		}

		POINT point;
		point.x = (LONG)position.X;
		point.y = (LONG)position.Y;

		if (!ClientToScreen(window, &point)) {
			return;
		}

		SetCursorPos(point.x, point.y);
		m_LastMousePosition = position;
	}

	void SetMousePosition(float x, float y) {
		auto window = static_cast<HWND>(Win32Window::GetNativeWindow());
		if (!IsWindow(window)) {
			return;
		}

		POINT point;
		point.x = (LONG)x;
		point.y = (LONG)y;

		if (!ClientToScreen(window, &point)) {
			return;
		}

		SetCursorPos(point.x, point.y);
		m_LastMousePosition = Vector2(x, y);
	}

	void CenterMouse() {
		auto window = static_cast<HWND>(Win32Window::GetNativeWindow());
		if (!IsWindow(window)) {
			return;
		}

		RECT client_area;
		GetClientRect(window, &client_area);

		float center_x = (float)(client_area.left + client_area.right) / 2.0f;
		float center_y = (float)(client_area.top + client_area.bottom) / 2.0f;

		SetMousePosition(Vector2(center_x, center_y));
	}

	void ClipMouse(bool clip) {
		auto window = static_cast<HWND>(Win32Window::GetNativeWindow());
		if (!IsWindow(window)) {
			return;
		}

		if (clip) {
			RECT clip_rect;
			GetClientRect(window, &clip_rect);

			POINT top_left = { clip_rect.left, clip_rect.top };
			POINT bottom_right = { clip_rect.right, clip_rect.bottom };

			ClientToScreen(window, &top_left);
			ClientToScreen(window, &bottom_right);

			clip_rect.left = top_left.x;
			clip_rect.top = top_left.y;
			clip_rect.right = bottom_right.x;
			clip_rect.bottom = bottom_right.y;

			ClipCursor(&clip_rect);
		}
		else {
			ClipCursor(nullptr);
		}
	}

	void ShowMouse(bool show) {
		if (m_MouseVisible == show) {
			return;
		}

		m_MouseVisible = show;
		ShowCursor(show);
	}

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

	bool IsMouseVisible() {
		return m_MouseVisible;
	}
}