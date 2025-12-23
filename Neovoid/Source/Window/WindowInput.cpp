#include "WindowInput.hpp"
#include "Platform/Windows/WindowsInput.hpp"

namespace WindowInput {
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
};