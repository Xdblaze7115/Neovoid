#include "Viewport.hpp"

Viewport::Viewport(int viewport_index, Vector2 positon, Vector2 size) {
	Viewport_Index = viewport_index;
	Position = positon;
	Size = size;
	Visible = true;

	Viewport_Frame.TopLeftX = Position.X;
	Viewport_Frame.TopLeftY = Position.Y;
	Viewport_Frame.Width = Size.X;
	Viewport_Frame.Height = Size.Y;
	Viewport_Frame.MinDepth = 0.0f;
	Viewport_Frame.MaxDepth = 1.0f;

	Aspect_Ratio = Size.X / Size.Y;

	Orthographic_Width = Orthographic_Height * Aspect_Ratio;
	Perspective_Matrix = XMMatrixPerspectiveFovLH(Fov, Aspect_Ratio, Near_Plane, Far_Plane);
	Orthographic_Matrix = XMMatrixOrthographicLH(Orthographic_Width, Orthographic_Height, Near_Plane, Far_Plane);
}

void Viewport::Update() {
	Viewport_Frame.TopLeftX = Position.X;
	Viewport_Frame.TopLeftY = Position.Y;
	Viewport_Frame.Width = Size.X;
	Viewport_Frame.Height = Size.Y;

	Aspect_Ratio = Size.X / Size.Y;

	Orthographic_Width = Orthographic_Height * Aspect_Ratio;
	Perspective_Matrix = XMMatrixPerspectiveFovLH(Fov, Aspect_Ratio, Near_Plane, Far_Plane);
	Orthographic_Matrix = XMMatrixOrthographicLH(Orthographic_Width, Orthographic_Height, Near_Plane, Far_Plane);
}

void Viewport::SetOrthographic(bool state) {
	Orthographic = state;
	Update();
}

void Viewport::SetPosition(Vector2 position) {
	Position = position;
	Update();
}

void Viewport::SetSize(Vector2 size) {
	Size = size;
	Update();
}

void Viewport::Show() {
	Visible = true;
	Update();
}

void Viewport::Hide() {
	Visible = false;
	Update();
}

D3D11_VIEWPORT* Viewport::GetViewportFrame() {
	return &Viewport_Frame;
}

XMMATRIX Viewport::GetProjectionMatrix() {
	if (Orthographic) {
		return Orthographic_Matrix;
	}
	else {
		return Perspective_Matrix;
	}
}

Vector2 Viewport::WorldToScreen(/*Matrix4 view_matrix, Matrix4 projection_matrix, Vector3 world_position*/) {
	/*float viewport_width = Size.X;
	float viewport_height = Size.Y;

	Vector4 clip = view_matrix * Vector4(
		world_position.X,
		world_position.Y,
		world_position.Z,
		1.0f
	);

	if (clip.W <= 0.0f) {
		return Vector2(-1.0f, -1.0f); // Behind Camera
	}

	clip = projection_matrix * clip;

	if (clip.W == 0.0f) {
		return Vector2(-1.0f, -1.0f);
	}

	float ndc_x = clip.X / clip.W;
	float ndc_y = clip.Y / clip.W;

	float screen_x = (ndc_x * 0.5f + 0.5f) * viewport_width;
	float screen_y = (1.0f - (ndc_y * 0.5f + 0.5f)) * viewport_height;
	return Vector2(screen_x, screen_y);*/
	return Vector2();
}

Vector2 Viewport::GetSize() {
	return Size;
}

Vector2 Viewport::GetPosition() {
	return Position;
}

bool Viewport::IsOrthographic() {
	return Orthographic;
}

float Viewport::GetAspectRatio() {
	return Aspect_Ratio;
}

float Viewport::GetNearPlane() {
	return Near_Plane;
}

float Viewport::GetFarPlane() {
	return Far_Plane;
}

float Viewport::GetFov() {
	return Fov;
}

bool Viewport::IsVisible() {
	return Visible;
}