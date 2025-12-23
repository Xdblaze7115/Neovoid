#pragma once
#include "Camera/Camera.hpp"
#include "Viewport/Viewport.hpp"
#include "Renderer/RendererContext.hpp"
#include "Renderer/Bindables/Buffer.hpp"

class Drawable {
private:
	IndexBuffer* m_IndexBuffer;
	std::vector<std::unique_ptr<Bindable>> m_Binds;
public:
	Drawable() = default;
	~Drawable() = default;
	void Draw();
	virtual void Update(float delta_time) = 0;
	void AddBind(std::unique_ptr<Bindable> bind);
	void SetIndexBuffer(std::unique_ptr<IndexBuffer> index_buffer);
	virtual Camera* GetCamera() = 0;
	virtual Viewport* GetViewport() = 0;
	virtual DirectX::XMMATRIX GetTransform() = 0;
};