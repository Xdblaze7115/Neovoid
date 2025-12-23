#include "Camera.hpp"

void Camera::Update() {
	XMMATRIX rotation_matrix = XMMatrixRotationRollPitchYaw(
		XMVectorGetX(Rotation),
		-XMVectorGetY(Rotation),
		XMVectorGetZ(Rotation)
	);
	Forward = XMVector3TransformCoord(XMVectorSet(0, 0, 1, 0), rotation_matrix);
	Up = XMVector3TransformCoord(XMVectorSet(0, 1, 0, 0), rotation_matrix);
	Right = XMVector3TransformCoord(XMVectorSet(1, 0, 0, 0), rotation_matrix);

	View_Matrix = XMMatrixLookToLH(Position, Forward, Up);
	Inverse_View_Matrix = XMMatrixInverse(nullptr, View_Matrix);
}

void Camera::LookAt(XMVECTOR target) {

}

void Camera::SetPosition(XMVECTOR position) {
	Position = position;
	Update();
}

void Camera::SetRotation(XMVECTOR rotation) {
	Rotation = rotation;
	Update();
}

XMVECTOR Camera::GetForwardVector() {
	return Forward;
}

XMVECTOR Camera::GetUpVector() {
	return Up;
}

XMVECTOR Camera::GetRightVector() {
	return Right;
}

XMVECTOR Camera::GetPosition() {
	return Position;
}

XMVECTOR Camera::GetRotation() {
	return Rotation;
}

XMMATRIX Camera::GetViewMatrix() {
	return View_Matrix;
}

XMMATRIX Camera::GetInverseViewMatrix() {
	return Inverse_View_Matrix;
}