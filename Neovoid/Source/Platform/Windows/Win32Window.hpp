#pragma once
#ifdef NEO_PLATFORM_WINDOWS
#include <Windows.h>
#endif
#include "VoidTypes.hpp"

namespace Win32Window {
	void Initialize(const WindowProps& props);
	void Shutdown();
	void Update();
	void SetEventCallback(const EventCallbackFn& callback);

	bool WindowIsOpen();
	void* GetNativeWindow();
	WindowProps& GetProps();
	Vector2 GetSize();
};