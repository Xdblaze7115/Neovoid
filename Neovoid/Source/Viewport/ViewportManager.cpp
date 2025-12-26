#include "ViewportManager.hpp"

namespace ViewportManager {
	std::vector<Viewport> Viewports;

	void Initialize() {
		//Vector2 window_size = Window::GetSize();
		//Viewports.clear();
		//Viewports.emplace_back(0, Vector2(0, 0), window_size);
	}

	void Update() {
		for (Viewport& viewport : Viewports) {
			//viewport.Update();
		}
	}

	Viewport* GetViewportByIndex(int index) {
		if (index >= 0 && index < Viewports.size()) {
			return &Viewports[index];
		}
		return nullptr;
	}

	std::vector<Viewport> GetViewports() {
		return Viewports;
	}
}