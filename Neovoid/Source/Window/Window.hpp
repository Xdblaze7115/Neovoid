#pragma once
#include "VoidTypes.hpp"

namespace Window {
	void Initialize(const WindowProps& props = WindowProps());
	void Shutdown();
	void Update();
	void SetEventCallback(const EventCallbackFn& callback);

	bool WindowIsOpen();
	void* GetNativeWindow();
	Vector2 GetSize();
};