#include "Window.hpp"
#include "Logging/Logging.hpp"
#include "Platform/Windows/Win32Window.hpp"

namespace Window {
	void Initialize(const WindowProps& props) {
		#ifdef NEO_PLATFORM_WINDOWS
			Win32Window::Initialize(props);
		#endif
	}

	void Shutdown() {
		#ifdef NEO_PLATFORM_WINDOWS
			Win32Window::Shutdown();
		#endif
	}

	void Update() {
		#ifdef NEO_PLATFORM_WINDOWS
			Win32Window::Update();
		#endif
	}

	void SetEventCallback(const EventCallbackFn& callback) {
		#ifdef NEO_PLATFORM_WINDOWS
			Win32Window::SetEventCallback(callback);
		#endif
	}

	bool WindowIsOpen() {
		#ifdef NEO_PLATFORM_WINDOWS
			return Win32Window::WindowIsOpen();
		#endif
	}

	void* GetNativeWindow() {
		#ifdef NEO_PLATFORM_WINDOWS
			return Win32Window::GetNativeWindow();
		#endif
	}

	Vector2 GetSize() {
		#ifdef NEO_PLATFORM_WINDOWS
			return Win32Window::GetSize();
		#endif
	}
};