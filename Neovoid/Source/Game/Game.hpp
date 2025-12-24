#pragma once
#include "Player/Player.hpp"

namespace Game {
	void Initialize();
	void BeginFrame();
	void EndFrame();
	void Update();
	Player* GetLocalPlayer();
};