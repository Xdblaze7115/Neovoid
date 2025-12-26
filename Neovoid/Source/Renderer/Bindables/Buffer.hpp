#pragma once
#include "Bindable.hpp"

class VertexBuffer : public Bindable {
private:
	UINT m_Stride = 0u;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
public:
	template<class V>
	VertexBuffer(std::vector<V>& vertices) {
		m_Stride = sizeof(V);
		D3D11_BUFFER_DESC vertex_buffer_desc = {};
		vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		vertex_buffer_desc.CPUAccessFlags = 0u;
		vertex_buffer_desc.MiscFlags = 0u;
		vertex_buffer_desc.ByteWidth = sizeof(V) * vertices.size();
		vertex_buffer_desc.StructureByteStride = sizeof(V);

		D3D11_SUBRESOURCE_DATA vertex_sub_data = {};
		vertex_sub_data.pSysMem = vertices.data();
		HRESULT hr = RendererContext::GetDevice()->CreateBuffer(&vertex_buffer_desc, &vertex_sub_data, &m_VertexBuffer);

		if (FAILED(hr)) {
			NEOLOG_ERROR("Failed to create vertex buffer");
		}
	}

	void Bind() noexcept override;
	void Unbind() noexcept override;
};

class IndexBuffer : public Bindable {
private:
	UINT m_Count;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_IndexBuffer;
public:
	IndexBuffer(std::vector<unsigned int>& indices);

	void Bind() noexcept override;
	void Unbind() noexcept override;

	UINT GetCount();
};