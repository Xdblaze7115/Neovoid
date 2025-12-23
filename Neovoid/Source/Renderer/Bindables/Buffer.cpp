#include "Buffer.hpp"

// Vertex Buffer //
void VertexBuffer::Bind() noexcept {
	UINT offset = 0u;
	RendererContext::GetDeviceContext()->IASetVertexBuffers(0u, 1u, m_VertexBuffer.GetAddressOf(), &m_Stride, &offset);
}

void VertexBuffer::Unbind() noexcept {
	ID3D11Buffer* null_buffer = nullptr;
	UINT stride = 0;
	UINT offset = 0;
	RendererContext::GetDeviceContext()->IASetVertexBuffers(0u, 1u, &null_buffer, &stride, &offset);
}

// Index Buffer //
IndexBuffer::IndexBuffer(std::vector<uint32_t>& indices) {
	m_Count = (UINT)indices.size();
	D3D11_BUFFER_DESC index_buffer_desc = {};
	index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	index_buffer_desc.CPUAccessFlags = 0u;
	index_buffer_desc.MiscFlags = 0u;
	index_buffer_desc.ByteWidth = sizeof(uint32_t) * m_Count;
	index_buffer_desc.StructureByteStride = sizeof(uint32_t);

	D3D11_SUBRESOURCE_DATA index_sub_data = {};
	index_sub_data.pSysMem = indices.data();
	HRESULT hr = RendererContext::GetDevice()->CreateBuffer(&index_buffer_desc, &index_sub_data, &m_IndexBuffer);

	if (FAILED(hr)) {
		NEOLOG_ERROR("Failed to create index buffer");
	}
}

void IndexBuffer::Bind() noexcept {
	UINT offset = 0u;
	RendererContext::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, offset);
}

void IndexBuffer::Unbind() noexcept {
	ID3D11Buffer* null_buffer = nullptr;
	UINT offset = 0u;
	RendererContext::GetDeviceContext()->IASetIndexBuffer(null_buffer, DXGI_FORMAT_R32_UINT, offset);
}

UINT IndexBuffer::GetCount() {
	return m_Count;
}