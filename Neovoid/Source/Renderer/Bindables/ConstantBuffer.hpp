#pragma once
#include "Bindable.hpp"

template<typename C>
class ConstantBuffer : public Bindable {
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> Constant_Buffer;
public:
	ConstantBuffer(C& constants) {
		D3D11_BUFFER_DESC constant_buffer_desc = {};
		constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constant_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		constant_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constant_buffer_desc.MiscFlags = 0u;
		constant_buffer_desc.ByteWidth = sizeof(constants);
		constant_buffer_desc.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA constant_sub_data = {};
		constant_sub_data.pSysMem = &constants;

		HRESULT hr = RendererContext::GetDevice()->CreateBuffer(&constant_buffer_desc, &constant_sub_data, &Constant_Buffer);
		if (FAILED(hr)) {
			NEOLOG_ERROR("Failed to create constant buffer");
		}
	};

	ConstantBuffer() {
		D3D11_BUFFER_DESC constant_buffer_desc = {};
		constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		constant_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
		constant_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		constant_buffer_desc.MiscFlags = 0u;
		constant_buffer_desc.ByteWidth = sizeof(C);
		constant_buffer_desc.StructureByteStride = 0u;

		HRESULT hr = RendererContext::GetDevice()->CreateBuffer(&constant_buffer_desc, nullptr, &Constant_Buffer);
		if (FAILED(hr)) {
			NEOLOG_ERROR("Failed to create constant buffer");
		}
	};

	void Update(C& constants) {
		D3D11_MAPPED_SUBRESOURCE mapped_subresource;
		RendererContext::GetDeviceContext()->Map(
			Constant_Buffer.Get(),
			0u,
			D3D11_MAP_WRITE_DISCARD,
			0u,
			&mapped_subresource
		);
		memcpy(mapped_subresource.pData, &constants, sizeof(constants));
		RendererContext::GetDeviceContext()->Unmap(Constant_Buffer.Get(), 0u);
	}
};

template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C> {
private:
	using ConstantBuffer<C>::Constant_Buffer;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind() noexcept override {
		RendererContext::GetDeviceContext()->VSSetConstantBuffers(0u, 1u, Constant_Buffer.GetAddressOf());
	}

	void Unbind() noexcept override {
		RendererContext::GetDeviceContext()->VSSetConstantBuffers(0u, 1u, nullptr);
	}
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C> {
private:
	using ConstantBuffer<C>::Constant_Buffer;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind() noexcept override {
		RendererContext::GetDeviceContext()->PSSetConstantBuffers(0u, 1u, Constant_Buffer.GetAddressOf());
	}

	void Unbind() noexcept override {
		RendererContext::GetDeviceContext()->PSSetConstantBuffers(0u, 1u, nullptr);
	}
};