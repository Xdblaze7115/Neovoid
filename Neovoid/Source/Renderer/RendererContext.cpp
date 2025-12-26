#include "RendererContext.hpp"
#include "Logging/Logging.hpp"
#include "Window/Window.hpp"
#include "imgui.h"

namespace RendererContext {
	bool m_VSync = false;
	Microsoft::WRL::ComPtr<ID3D11Device> m_Device = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_RasterizerState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_BlendState = nullptr;

	void Initialize() {
		Vector2 size = Window::GetSize();
		DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
		swap_chain_desc.BufferCount = 2; // The number of back buffers to use in the swap chain
		swap_chain_desc.BufferDesc.Width = size.X;
		swap_chain_desc.BufferDesc.Height = size.Y;
		swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swap_chain_desc.BufferDesc.RefreshRate.Numerator = 120;
		swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
		swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swap_chain_desc.SampleDesc.Count = 1;
		swap_chain_desc.SampleDesc.Quality = 0;
		swap_chain_desc.OutputWindow = (HWND)Window::GetNativeWindow();
		swap_chain_desc.Windowed = TRUE;

		UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL feature_levels = D3D_FEATURE_LEVEL_11_0;
		D3D_FEATURE_LEVEL feature_level;
		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flags,
			&feature_levels,
			1,
			D3D11_SDK_VERSION,
			&swap_chain_desc,
			m_SwapChain.GetAddressOf(),
			m_Device.GetAddressOf(),
			&feature_level,
			m_DeviceContext.GetAddressOf()
		);

		if (FAILED(hr)) {
			NEOLOG_ERROR("Failed to create DirectX 11 device and swap chain");
			return;
		}
		NEOLOG_INFO("Created Device -> 0x%p", (void*)m_Device.GetAddressOf());
		NEOLOG_INFO("Created Swap Chain -> 0x%p", (void*)m_SwapChain.GetAddressOf());
		NEOLOG_INFO("Created Device Context -> 0x%p", (void*)m_DeviceContext.GetAddressOf());

		Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer = nullptr;
		hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(back_buffer.GetAddressOf()));
		if (FAILED(hr)) {
			NEOLOG_ERROR("Failed to get back buffer");
			return;
		}
		NEOLOG_INFO("Found Back Buffer -> 0x%p", (void*)back_buffer.GetAddressOf());

		hr = m_Device->CreateRenderTargetView(back_buffer.Get(), nullptr, m_RenderTargetView.GetAddressOf());
		back_buffer.Reset();
		if (FAILED(hr)) {
			NEOLOG_ERROR("Failed to create render target view");
			return;
		}
		NEOLOG_INFO("Created Render Target View -> 0x%p", (void*)m_RenderTargetView.GetAddressOf());

		D3D11_DEPTH_STENCIL_DESC depth_stencil_state_desc = {};
		depth_stencil_state_desc.DepthEnable = TRUE;
		depth_stencil_state_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depth_stencil_state_desc.DepthFunc = D3D11_COMPARISON_LESS;
		depth_stencil_state_desc.StencilEnable = FALSE;

		m_Device->CreateDepthStencilState(&depth_stencil_state_desc, &m_DepthStencilState);
		m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState.Get(), 1u);
		NEOLOG_INFO("Created Depth Stencil State -> 0x%p", (void*)m_DepthStencilState.GetAddressOf());

		Microsoft::WRL::ComPtr<ID3D11Texture2D> depth_texture;
		D3D11_TEXTURE2D_DESC depth_texture_desc = {};
		depth_texture_desc.Width = size.X;
		depth_texture_desc.Height = size.Y;
		depth_texture_desc.MipLevels = 1u;
		depth_texture_desc.ArraySize = 1u;
		depth_texture_desc.Format = DXGI_FORMAT_D32_FLOAT;
		depth_texture_desc.SampleDesc.Count = 1u;
		depth_texture_desc.SampleDesc.Quality = 0u;
		depth_texture_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		m_Device->CreateTexture2D(&depth_texture_desc, nullptr, &depth_texture);

		D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc = {};
		depth_stencil_view_desc.Format = DXGI_FORMAT_D32_FLOAT;
		depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depth_stencil_view_desc.Texture2D.MipSlice = 0u;

		hr = m_Device->CreateDepthStencilView(depth_texture.Get(), &depth_stencil_view_desc, &m_DepthStencilView);
		if (FAILED(hr)) {
			NEOLOG_ERROR("Failed to create depth stencil view");
			return;
		}
		NEOLOG_INFO("Created Depth Stencil View -> 0x%p", (void*)m_DepthStencilView.GetAddressOf());

		D3D11_RASTERIZER_DESC rasterizer_desc;
		rasterizer_desc.AntialiasedLineEnable = FALSE;
		rasterizer_desc.CullMode = D3D11_CULL_NONE; // D3D11_CULL_NONE | D3D11_CULL_BACK
		rasterizer_desc.DepthBias = 0;
		rasterizer_desc.DepthBiasClamp = 0.0f;
		rasterizer_desc.DepthClipEnable = TRUE;
		rasterizer_desc.FillMode = D3D11_FILL_SOLID; // D3D11_FILL_SOLID | D3D11_FILL_WIREFRAME
		rasterizer_desc.FrontCounterClockwise = FALSE;
		rasterizer_desc.MultisampleEnable = FALSE;
		rasterizer_desc.ScissorEnable = FALSE;
		rasterizer_desc.SlopeScaledDepthBias = 0.0f;

		hr = m_Device->CreateRasterizerState(&rasterizer_desc, &m_RasterizerState);
		if (FAILED(hr)) {
			NEOLOG_ERROR("Failed to create rasterizer state");
			return;
		}
		NEOLOG_INFO("Created Rasterizer State -> 0x%p", (void*)m_RasterizerState.GetAddressOf());

		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		D3D11_BLEND_DESC blend_desc = {};
		blend_desc.RenderTarget[0].BlendEnable = TRUE;
		blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		hr = m_Device->CreateBlendState(&blend_desc, &m_BlendState);
		if (FAILED(hr)) {
			NEOLOG_ERROR("Failed to create blend state");
			return;
		}
		NEOLOG_INFO("Created Blend State -> 0x%p", (void*)m_BlendState.GetAddressOf());
		m_DeviceContext->OMSetBlendState(m_BlendState.Get(), blendFactor, 0xFFFFFFFF);

		m_DeviceContext->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());
		NEOLOG_INFO("DirectX 11 initialized successfully");
	}

	void ResizeBuffers(int width, int height) {
		if (!m_SwapChain) {
			return;
		}

		m_RenderTargetView.Reset();
		m_DepthStencilView.Reset();

		HRESULT hr = m_SwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
		if (FAILED(hr)) {
			NEOLOG_ERROR("Failed to resize buffers");
			return;
		}

		Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer = nullptr;
		hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(back_buffer.GetAddressOf()));
		if (FAILED(hr)) {
			NEOLOG_ERROR("Failed to get back buffer");
			return;
		}
		m_Device->CreateRenderTargetView(back_buffer.Get(), nullptr, m_RenderTargetView.GetAddressOf());

		Microsoft::WRL::ComPtr<ID3D11Texture2D> depth_texture;
		D3D11_TEXTURE2D_DESC depth_texture_desc = {};
		depth_texture_desc.Width = width;
		depth_texture_desc.Height = height;
		depth_texture_desc.MipLevels = 1u;
		depth_texture_desc.ArraySize = 1u;
		depth_texture_desc.Format = DXGI_FORMAT_D32_FLOAT;
		depth_texture_desc.SampleDesc.Count = 1u;
		depth_texture_desc.SampleDesc.Quality = 0u;
		depth_texture_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		m_Device->CreateTexture2D(&depth_texture_desc, nullptr, &depth_texture);

		D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc = {};
		depth_stencil_view_desc.Format = DXGI_FORMAT_D32_FLOAT;
		depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depth_stencil_view_desc.Texture2D.MipSlice = 0u;
		m_Device->CreateDepthStencilView(depth_texture.Get(), &depth_stencil_view_desc, &m_DepthStencilView);

		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState.Get(), 1u);
		m_DeviceContext->OMSetBlendState(m_BlendState.Get(), blendFactor, 0xFFFFFFFF);
		m_DeviceContext->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());
	}

	void Clear(float r, float g, float b, float a) {
		if (!m_RenderTargetView || !m_DepthStencilView) {
			return;
		}

		float color[4] = { r, g, b, a };
		m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), color);
		m_DeviceContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);

		float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		m_DeviceContext->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), m_DepthStencilView.Get());
		m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState.Get(), 1u);
		m_DeviceContext->RSSetState(m_RasterizerState.Get());
		m_DeviceContext->OMSetBlendState(m_BlendState.Get(), blendFactor, 0xFFFFFFFF);
	}

	void Present() {
		m_SwapChain->Present(m_VSync ? 1 : 0, 0);
	}

	void SetVSync(bool state) {
		m_VSync = state;
	}

	// Imgui
	void InitializeImgui() {
		ImGui_ImplWin32_EnableDpiAwareness();
		ImGui_ImplWin32_Init(Window::GetNativeWindow());
		ImGui_ImplDX11_Init(m_Device.Get(), m_DeviceContext.Get());
	}

	void ShutdownImgui() {
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
	}

	void BeginImguiFrame() {
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
	}

	void EndImguiFrame() {
		ImGuiIO& io = ImGui::GetIO();
		Vector2 size = Window::GetSize();
		io.DisplaySize = ImVec2(size.X, size.Y);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

	// Renderer
	bool GetVSync() {
		return m_VSync;
	}

	ID3D11Device* GetDevice() {
		return m_Device.Get();
	}

	ID3D11DeviceContext* GetDeviceContext() {
		return m_DeviceContext.Get();
	}

	IDXGISwapChain* GetSwapChain() {
		return m_SwapChain.Get();
	}
}