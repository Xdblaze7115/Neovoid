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
	static float mouse_sensitivity = 0.005f;
	static Vector2 last_mouse_position = Vector2(0, 0);
    static bool first_mouse = true;

    float move_speed = 5.0f;
    float move_amount = move_speed * delta_time;

    XMVECTOR move_direction = XMVectorZero();
    if (WindowInput::IsKeyPressed(NEO_KEY_W)) {
        move_direction += m_Camera.GetForwardVector();
    }
    if (WindowInput::IsKeyPressed(NEO_KEY_S)) {
        move_direction -= m_Camera.GetForwardVector();
    }
    if (WindowInput::IsKeyPressed(NEO_KEY_A)) {
        move_direction -= m_Camera.GetRightVector();
    }
    if (WindowInput::IsKeyPressed(NEO_KEY_D)) {
        move_direction += m_Camera.GetRightVector();
    }
    if (WindowInput::IsKeyPressed(NEO_KEY_SPACE)) {
        move_direction += m_Camera.GetUpVector();
    }
    if (WindowInput::IsKeyPressed(NEO_KEY_CONTROL)) {
        move_direction -= m_Camera.GetUpVector();
    }

    if (XMVectorGetX(XMVector3LengthSq(move_direction)) > 0.01f) {
        move_direction = XMVector3Normalize(move_direction);
        m_Camera.SetPosition(m_Camera.GetPosition() + move_direction * move_amount);
    }

    if (WindowInput::IsMouseButtonPressed(NEO_MOUSE_BUTTON_RIGHT)) {
        Vector2 mouse_position = WindowInput::GetMousePosition();

        if (first_mouse) {
            last_mouse_position = mouse_position;
            first_mouse = false;
        }

        float delta_x = mouse_position.X - last_mouse_position.X;
        float delta_y = mouse_position.Y - last_mouse_position.Y;
        WindowInput::SetMousePosition(last_mouse_position);
        
        delta_x *= mouse_sensitivity;
        delta_y *= mouse_sensitivity;

        XMVECTOR rotation = m_Camera.GetRotation();
        float pitch = XMVectorGetX(rotation) - delta_y;
        float yaw = XMVectorGetY(rotation) - delta_x;
        m_Camera.SetRotation(XMVectorSet(pitch, yaw, 0.0f, 0.0f));
    }
    else {
        first_mouse = true;
    }
}

void Player::Respawn() {

}

void Player::TakeDamage() {

}

Camera* Player::GetCamera() {
	return &m_Camera;
}