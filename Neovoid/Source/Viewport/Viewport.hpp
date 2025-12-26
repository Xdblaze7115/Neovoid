#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Math/Vector.hpp"
#include "Window/Window.hpp"
using namespace DirectX;

class Viewport {
private:
	D3D11_VIEWPORT Viewport_Frame = {};
	int Viewport_Index = 0;
	bool Orthographic = false;
	Vector2 Position = Vector2(0.0f, 0.0f);
	Vector2 Size = Vector2(0.0f, 0.0f);
	float Aspect_Ratio = 1.0f;
	float Near_Plane = 0.005f;
	float Far_Plane = 256.0f;
	float Fov = 1.0f;
	float Orthographic_Height = 10.0f;
	float Orthographic_Width = 5.0f;
	bool Visible = true;

	XMMATRIX Perspective_Matrix = XMMatrixPerspectiveFovLH(Fov, Aspect_Ratio, Near_Plane, Far_Plane); // Projection Matrix
	XMMATRIX Orthographic_Matrix = XMMatrixOrthographicLH(Orthographic_Width, Orthographic_Height, Near_Plane, Far_Plane); // Projection Matrix
public:
	Viewport() = default;
	Viewport(int viewport_index, Vector2 positon, Vector2 size);
	void Update();
	void SetOrthographic(bool state);
	void SetPosition(Vector2 position);
	void SetSize(Vector2 size);
	void Show();
	void Hide();

	D3D11_VIEWPORT* GetViewportFrame();
	XMMATRIX GetProjectionMatrix();
	Vector2 WorldToScreen(/*Matrix4 view_matrix, Matrix4 projection_matrix, Vector3 world_position*/);
	Vector2 GetPosition();
	Vector2 GetSize();
	bool IsOrthographic();
	float GetAspectRatio();
	float GetNearPlane();
	float GetFarPlane();
	float GetFov();
	bool IsVisible();
};