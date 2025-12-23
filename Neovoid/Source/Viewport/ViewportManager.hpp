#pragma once
#include <vector>
#include "Viewport.hpp"

namespace ViewportManager {
	void Initialize();
	void Update();

	Viewport* GetViewportByIndex(int index);
	std::vector<Viewport> GetViewports();
}