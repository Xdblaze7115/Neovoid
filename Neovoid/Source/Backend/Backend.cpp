#include "Backend.hpp"
#include "Logging/Logging.hpp"
#include "Imgui/imgui.hpp"
#include "Window/Window.hpp"
#include "Renderer/Renderer.hpp"
#include "Viewport/ViewportManager.hpp"
#include "Game/Game.hpp"

namespace Backend {
	void Initialize() {
		Logging::Initialize();
		Window::Initialize();
		Renderer::Initialize();
		ViewportManager::Initialize();
		Imgui::Initialize();
		Game::Initialize();
	}

	void Shutdown() {
		Imgui::Shutdown();
		Window::Shutdown();
		Logging::Shutdown();
	}

	void UpdateSubSystems() {

	}

	void BeginFrame() {
		Renderer::BeginFrame();
		Imgui::BeginFrame();
		Game::BeginFrame();
	}

	void EndFrame() {
		Imgui::EndFrame();
		Game::EndFrame();
		Renderer::EndFrame();
	}

	void Update() {
		Window::Update();
		ViewportManager::Update();
		Imgui::Update();
		Game::Update();
		Renderer::Update();
	}
};