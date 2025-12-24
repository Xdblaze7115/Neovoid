#include "Player.hpp"
#include "Window/WindowInput.hpp"

void Player::Initialize() {

}

void Player::BeginFrame() {

}

void Player::EndFrame() {

}

void Player::Update(float delta_time) {
	UpdateCamera(delta_time);
}

void Player::UpdateCamera(float delta_time) {
	static float g_Camera_Sensitivity = 0.002f;
	static Vector2 g_Last_Mouse_Position = Vector2(0, 0);

	if (WindowInput::IsKeyPressed(NEO_KEY_W)) {
		m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetForwardVector() * delta_time);
	}
	else if (WindowInput::IsKeyPressed(NEO_KEY_S)) {
		m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetForwardVector() * delta_time);
	}
	else if (WindowInput::IsKeyPressed(NEO_KEY_A)) {
		m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetRightVector() * delta_time);
	}
	else if (WindowInput::IsKeyPressed(NEO_KEY_D)) {
		m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetRightVector() * delta_time);
	}
	else if (WindowInput::IsKeyPressed(NEO_KEY_SPACE)) {
		m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetUpVector() * delta_time);
	}
	else if (WindowInput::IsKeyPressed(NEO_KEY_CONTROL)) {
		m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetUpVector() * delta_time);
	}

	if (WindowInput::IsMouseButtonPressed(NEO_MOUSE_BUTTON_RIGHT)) {
		Vector2 mouse_position = WindowInput::GetMousePosition();

		if (g_Last_Mouse_Position.X != 0 && g_Last_Mouse_Position.Y != 0) {
			float delta_x = mouse_position.X - g_Last_Mouse_Position.X;
			float delta_y = mouse_position.Y - g_Last_Mouse_Position.Y;

			delta_x *= g_Camera_Sensitivity;
			delta_y *= g_Camera_Sensitivity;

			XMVECTOR rotation = m_Camera.GetRotation();
			m_Camera.SetRotation(rotation + XMVectorSet(delta_y, -delta_x, 0.0f, 0.0f));
		}
		g_Last_Mouse_Position = mouse_position;
	}
	else {
		g_Last_Mouse_Position = Vector2(0, 0);
	}
	m_Camera.Update();
}

void Player::Respawn() {

}

void Player::TakeDamage() {

}

Camera* Player::GetCamera() {
	return &m_Camera;
}