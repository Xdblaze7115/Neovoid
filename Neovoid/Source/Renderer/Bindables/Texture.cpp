#include "Texture.hpp"

Texture::Texture(TextureResource* texture_resource, UINT start_slot) {
	m_StartSlot = start_slot;
	m_ShaderResourceView = texture_resource->GetShaderResourceView();

	D3D11_SAMPLER_DESC sampler_desc = {};
	sampler_desc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MaxAnisotropy = 16;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampler_desc.MinLOD = 0;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT hr = RendererContext::GetDevice()->CreateSamplerState(&sampler_desc, &m_SamplerState);
	if (FAILED(hr)) {
		NEOLOG_ERROR("Failed to create sampler state for texture");
	}
}

void Texture::Bind() noexcept {
	RendererContext::GetDeviceContext()->VSSetShaderResources(m_StartSlot, 1u, &m_ShaderResourceView);
	RendererContext::GetDeviceContext()->PSSetShaderResources(m_StartSlot, 1u, &m_ShaderResourceView);
	RendererContext::GetDeviceContext()->VSSetSamplers(m_StartSlot, 1u, m_SamplerState.GetAddressOf());
	RendererContext::GetDeviceContext()->PSSetSamplers(m_StartSlot, 1u, m_SamplerState.GetAddressOf());
}

void Texture::Unbind() noexcept {
	RendererContext::GetDeviceContext()->VSSetShaderResources(m_StartSlot, 1u, nullptr);
	RendererContext::GetDeviceContext()->PSSetShaderResources(m_StartSlot, 1u, nullptr);
	RendererContext::GetDeviceContext()->VSSetSamplers(m_StartSlot, 1u, nullptr);
	RendererContext::GetDeviceContext()->PSSetSamplers(m_StartSlot, 1u, nullptr);
}