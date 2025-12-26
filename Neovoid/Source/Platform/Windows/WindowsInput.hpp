#pragma once
#include "Math/Vector.hpp"

namespace WindowsInput {
	void SetMousePosition(Vector2 position);
	void SetMousePosition(float x, float y);
	void CenterMouse();
	void ClipMouse(bool clip);
	void ShowMouse(bool show);

	bool IsKeyPressed(int keycode);
	bool IsMouseButtonPressed(int button);
	Vector2 GetMousePosition();
	bool IsMouseVisible();
};