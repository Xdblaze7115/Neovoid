#pragma once
#ifdef NEO_PLATFORM_WINDOWS
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl/client.h>
#include "Backends/imgui_impl_dx11.h"
#include "Backends/imgui_impl_win32.h"
#endif

namespace RendererContext {
	// Renderer
	void Initialize();
	void ResizeBuffers(int width, int height);
	void Clear(float r, float g, float b, float a);
	void Present();
	void SetVSync(bool state);

	// Imgui
	void InitializeImgui();
	void ShutdownImgui();
	void BeginImguiFrame();
	void EndImguiFrame();

	// Renderer
	bool GetVSync();
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	IDXGISwapChain* GetSwapChain();
};