#include "Win32Window.hpp"
#include "Logging/Logging.hpp"
#include "Renderer/RendererContext.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/KeyEvent.hpp"

namespace Win32Window {
	bool s_Com_Initialized = false;
	bool m_Window_Is_Open = false;
	HWND m_Window = nullptr;
	WindowProps m_Props;

	void ProcessMessages() {
		MSG msg = {};
		while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT u_msg, WPARAM w_param, LPARAM l_param) {
		WindowProps& props = Win32Window::GetProps();
		switch (u_msg) {
		case WM_CLOSE: { // Window Closed
			m_Window_Is_Open = false;
			return 0;
		}
		case WM_SIZE: { // Window Resized
			if (w_param == SIZE_MINIMIZED) {
				break;
			}

			int width = LOWORD(l_param);
			int height = HIWORD(l_param);

			RendererContext::ResizeBuffers(width, height);
			props.Size = Vector2((float)width, (float)height);
			WindowResizeEvent event(width, height);
			//props.EventCallback(event);
			break;
		}
		case WM_KILLFOCUS: { // Window Focus Lost
			break;
		}
		case WM_KEYDOWN: // Key Pressed
		case WM_SYSKEYDOWN: {
			if ((l_param & 0x40000000)) { // Repeating Key Press
				KeyPressedEvent event((unsigned int)w_param, 1);
				//props.EventCallback(event);
				break;
			}
			else { // Not Repeating Key Press
				KeyPressedEvent event((unsigned int)w_param, 0);
				//props.EventCallback(event);
				break;
			}
		}
		case WM_KEYUP: // Key Released
		case WM_SYSKEYUP: {
			KeyReleasedEvent event((unsigned int)w_param);
			//props.EventCallback(event);
			break;
		}
		case WM_CHAR: {
			KeyTypedEvent event((unsigned int)w_param);
			//props.EventCallback(event);
			break;
		}
		case WM_MOUSEMOVE: { // Mouse Movement
			POINTS point = MAKEPOINTS(l_param);
			MouseMovedEvent event((float)point.x, (float)point.y);
			//props.EventCallback(event);
			break;
		}
		case WM_LBUTTONDOWN: { // Left Mouse Button Pressed
			int button = 0;
			SetCapture(hwnd);
			MouseButtonPressedEvent event(button);
			//props.EventCallback(event);
			break;
		}
		case WM_RBUTTONDOWN: { // Right Mouse Button Pressed
			int button = 1;
			MouseButtonPressedEvent event(button);
			//props.EventCallback(event);
			break;
		}
		case WM_MBUTTONDOWN: { // Middle Mouse Button Pressed
			int button = 2;
			MouseButtonPressedEvent event(button);
			//props.EventCallback(event);
			break;
		}
		case WM_XBUTTONDOWN: { // Side Mouse Button Pressed
			int button = (HIWORD(w_param) == XBUTTON1) ? 3 : 4;
			MouseButtonPressedEvent event(button);
			//props.EventCallback(event);
			break;
		}
		case WM_LBUTTONUP: { // Left Mouse Button Released
			int button = 0;
			ReleaseCapture();
			MouseButtonReleasedEvent event(button);
			//props.EventCallback(event);
			break;
		}
		case WM_RBUTTONUP: { // Right Mouse Button Released
			int button = 1;
			MouseButtonReleasedEvent event(button);
			//props.EventCallback(event);
			break;
		}
		case WM_MBUTTONUP: { // Middle Mouse Button Released
			int button = 2;
			MouseButtonReleasedEvent event(button);
			//props.EventCallback(event);
			break;
		}
		case WM_XBUTTONUP: { // Side Mouse Button Released
			int button = (HIWORD(w_param) == XBUTTON1) ? 3 : 4;
			MouseButtonReleasedEvent event(button);
			//props.EventCallback(event);
			break;
		}
		case WM_MOUSEWHEEL: { // Vertical Mouse Wheel Scrolled
			int delta = GET_WHEEL_DELTA_WPARAM(w_param);
			float scroll_amount = delta / (float)WHEEL_DELTA;

			MouseScrolledEvent event(0, scroll_amount);
			//props.EventCallback(event);
			break;
		}
		case WM_MOUSEHWHEEL: { // Horizontal Mouse Wheel Scrolled
			int delta = GET_WHEEL_DELTA_WPARAM(w_param);
			float scroll_amount = delta / (float)WHEEL_DELTA;

			MouseScrolledEvent event(scroll_amount, 0);
			//props.EventCallback(event);
			break;
		}
		}
		return DefWindowProc(hwnd, u_msg, w_param, l_param);
	}

	void Initialize(const WindowProps& props) {
		m_Props = props;
		NEOLOG_INFO("Creating Window -> %s [%.f, %.f]", m_Props.Title.c_str(), m_Props.Size.X, m_Props.Size.Y);

		// Initialize Com and create a window
		if (!s_Com_Initialized) {
			HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
			if (FAILED(hr)) {
				NEOLOG_ERROR("Failed to initialize Windows Com Object");
				return;
			}
			s_Com_Initialized = true;
		}

		WNDCLASSEX wc{};
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = &WindowProcedure;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetModuleHandle(nullptr);
		wc.hIcon = nullptr;
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = (LPCWSTR)m_Props.Title.c_str();
		wc.hIconSm = nullptr;

		if (!RegisterClassEx(&wc)) {
			NEOLOG_ERROR("Failed to register window class");
			return;
		}

		DWORD window_flags = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | (m_Props.IsResizeable ? WS_THICKFRAME : 0);
		RECT rect{ 0, 0, (LONG)m_Props.Size.X, (LONG)m_Props.Size.Y };
		AdjustWindowRect(&rect, window_flags, false);

		m_Window = CreateWindowExW(
			NULL,
			wc.lpszClassName,
			L"Neovoid",
			window_flags,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rect.right - rect.left,
			rect.bottom - rect.top,
			nullptr,
			nullptr,
			wc.hInstance,
			nullptr // Store The Window Class Instance For Later Use
		);

		if (!m_Window) {
			NEOLOG_ERROR("Failed to create window");
			return;
		}
		ShowWindow(m_Window, SW_SHOW);
		m_Window_Is_Open = true;
		NEOLOG_INFO("Created Window -> 0x%p", (void*)m_Window);
	}

	void Shutdown() {
		DestroyWindow(m_Window);
		CoUninitialize();
	}

	void Update() {
		ProcessMessages();
	}

	void SetEventCallback(const EventCallbackFn& callback) {
		m_Props.EventCallback = callback;
	}

	bool WindowIsOpen() {
		return m_Window_Is_Open;
	}

	void* GetNativeWindow() {
		return m_Window;
	}

	WindowProps& GetProps() {
		return m_Props;
	}

	Vector2 GetSize() {
		return m_Props.Size;
	}
}