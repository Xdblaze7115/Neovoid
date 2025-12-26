#pragma once
#include "Nodes/Player/Player.hpp"

namespace Game {
	void Initialize();
	void BeginFrame();
	void EndFrame();
	void Update();
	Player* GetLocalPlayer();
};