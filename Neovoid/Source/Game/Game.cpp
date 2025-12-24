#include <chrono>
#include "Game.hpp"
#include "VoidTypes.hpp"
#include "Logging/Logging.hpp"
#include "World/World.hpp"

namespace Game {
	float m_time_wrap = 10000.0f;
	float m_delta_time = 0.0f;
	float m_total_time = 0.0f;
	float m_fixed_delta_time = 1.0f / 60.0f;
	float m_delta_accumulator = 0.0f;

	GameState m_GameState = GameState::None;
	Player m_LocalPlayer;

	void Initialize() {
		m_GameState = GameState::World;
		m_LocalPlayer = Player();

		m_LocalPlayer.Initialize();
		World::Initialize();
	}

	void BeginFrame() {
		World::BeginFrame();
	}

	void EndFrame() {
		World::EndFrame();
	}

	void Update() {
		using clock = std::chrono::steady_clock;
		static auto previous_time = clock::now();
		auto current_time = clock::now();

		std::chrono::duration<float> duration = current_time - previous_time;
		previous_time = current_time;
		m_delta_time = duration.count();
		m_delta_accumulator += m_delta_time;

		m_total_time += m_delta_time;
		if (m_total_time > m_time_wrap) {
			m_total_time -= m_time_wrap;
		}

		m_LocalPlayer.Update(m_delta_time);
		World::Update(m_delta_time);

		while (m_delta_accumulator >= m_fixed_delta_time) {
			// Physics::StepPhysics(fixed_delta_time);
			m_delta_accumulator -= m_fixed_delta_time;
		}
	}

	Player* GetLocalPlayer() {
		return &m_LocalPlayer;
	}
}