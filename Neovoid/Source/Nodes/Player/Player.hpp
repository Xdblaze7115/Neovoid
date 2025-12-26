#pragma once
#include "Nodes/Camera/Camera.hpp"

class Player {
private:
	Camera m_Camera;
	float m_WalkSpeed = 10.0f;
	float m_JumpSpeed = 5.0f;
public:
	void Initialize();
	void BeginFrame();
	void EndFrame();
	void Update(float delta_time);
	void UpdateCamera(float delta_time);
	void Respawn();
	void TakeDamage();

	Camera* GetCamera();
};