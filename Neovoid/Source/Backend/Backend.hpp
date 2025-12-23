#pragma once
#include "VoidTypes.hpp"

namespace Backend {
	void Initialize();
	void Shutdown();
	void UpdateSubSystems();
	void BeginFrame();
	void EndFrame();
	void Update();
};