#pragma once
#include "Math/Vector.hpp"
#include "KeyCodes.hpp"

namespace WindowInput {
	bool IsKeyPressed(int keycode);
	bool IsMouseButtonPressed(int button);
	Vector2 GetMousePosition();
};