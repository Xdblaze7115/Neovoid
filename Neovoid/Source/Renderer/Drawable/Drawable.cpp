#include "Drawable.hpp"

void Drawable::Draw() {
	for (auto& bind : m_Binds) {
		bind->Bind();
	}
	RendererContext::GetDeviceContext()->DrawIndexed(m_IndexBuffer->GetCount(), 0u, 0u);
}

void Drawable::AddBind(std::unique_ptr<Bindable> bind) {
	m_Binds.push_back(std::move(bind));
}

void Drawable::SetIndexBuffer(std::unique_ptr<IndexBuffer> index_buffer) {
	m_IndexBuffer = index_buffer.get();
	m_Binds.push_back(std::move(index_buffer));
}