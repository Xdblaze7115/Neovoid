#include "WindowInput.hpp"
#include "Platform/Windows/WindowsInput.hpp"

namespace WindowInput {
	void SetMousePosition(Vector2 position) {
		#ifdef NEO_PLATFORM_WINDOWS
			WindowsInput::SetMousePosition(position);
		#endif
	}

	void SetMousePosition(float x, float y) {
		#ifdef NEO_PLATFORM_WINDOWS
			WindowsInput::SetMousePosition(x, y);
		#endif
	}

	void CenterMouse() {
		#ifdef NEO_PLATFORM_WINDOWS
			WindowsInput::CenterMouse();
		#endif
	}

	void ClipMouse(bool clip) {
		#ifdef NEO_PLATFORM_WINDOWS
			WindowsInput::ClipMouse(clip);
		#endif
	}

	void ShowMouse(bool show) {
		#ifdef NEO_PLATFORM_WINDOWS
			WindowsInput::ShowMouse(show);
		#endif
	}

	bool IsKeyPressed(int keycode) {
		#ifdef NEO_PLATFORM_WINDOWS
			return WindowsInput::IsKeyPressed(keycode);
		#endif
	}

	bool IsMouseButtonPressed(int button) {
		#ifdef NEO_PLATFORM_WINDOWS
			return WindowsInput::IsMouseButtonPressed(button);
		#endif
	}

	Vector2 GetMousePosition() {
		#ifdef NEO_PLATFORM_WINDOWS
			return WindowsInput::GetMousePosition();
		#endif
	}

	bool IsMouseVisible(){
		#ifdef NEO_PLATFORM_WINDOWS
			return WindowsInput::IsMouseVisible();
		#endif
	}
};