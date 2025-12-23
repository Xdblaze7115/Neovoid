#pragma once
#include "Math/Vector.hpp"

namespace WindowsInput {
	bool IsKeyPressed(int keycode);
	bool IsMouseButtonPressed(int button);
	Vector2 GetMousePosition();
};