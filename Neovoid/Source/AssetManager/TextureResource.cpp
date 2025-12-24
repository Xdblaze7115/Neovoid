#include <filesystem>
#include <DirectXTex.h>
#include "TextureResource.hpp"
#include "Logging/Logging.hpp"
#include "Renderer/RendererContext.hpp"

TextureResource::TextureResource(const wchar_t* file_path) {
	if (!std::filesystem::exists(file_path)) {
		NEOLOG_ERROR("Texture file does not exist: {}", std::filesystem::path(file_path).string());
		return;
	}

	DirectX::ScratchImage scratch_image;
	HRESULT hr = DirectX::LoadFromWICFile(file_path, DirectX::WIC_FLAGS_NONE, nullptr, scratch_image);

	if (FAILED(hr)) {
		std::wstring wstr(file_path);
		std::string str(wstr.begin(), wstr.end());
		NEOLOG_ERROR("Failed to load texture from file: {}", str);
		return;
	}

	bool mipmaps_generated = false;
	DirectX::ScratchImage mip_chain;

	if (scratch_image.GetMetadata().mipLevels == 1) {
		hr = DirectX::GenerateMipMaps(
			*scratch_image.GetImage(0, 0, 0),
			DirectX::TEX_FILTER_DEFAULT,
			0,
			mip_chain
		);

		if (SUCCEEDED(hr)) {
			mipmaps_generated = true;

			hr = DirectX::CreateTexture(
				RendererContext::GetDevice(),
				mip_chain.GetImages(),
				mip_chain.GetImageCount(),
				mip_chain.GetMetadata(),
				&m_Texture
			);

			if (FAILED(hr)) {
				NEOLOG_ERROR("Failed to create texture resource from mip chain");
				return;
			}
		}
		else {
			NEOLOG_ERROR("Failed to generate mipmaps, using original texture");
			mipmaps_generated = false;
		}
	}

	if (!mipmaps_generated) {
		hr = DirectX::CreateTexture(
			RendererContext::GetDevice(),
			scratch_image.GetImages(),
			scratch_image.GetImageCount(),
			scratch_image.GetMetadata(),
			&m_Texture
		);

		if (FAILED(hr)) {
			NEOLOG_ERROR("Failed to create texture resource from scratch image");
			return;
		}
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC shader_resource_view_desc = {};
	shader_resource_view_desc.Format = scratch_image.GetMetadata().format;
	shader_resource_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	if (mipmaps_generated) {
		shader_resource_view_desc.Texture2D.MipLevels = mip_chain.GetMetadata().mipLevels;
	}
	else {
		shader_resource_view_desc.Texture2D.MipLevels = scratch_image.GetMetadata().mipLevels;
	}
	shader_resource_view_desc.Texture2D.MostDetailedMip = 0;

	hr = RendererContext::GetDevice()->CreateShaderResourceView(
		m_Texture.Get(),
		&shader_resource_view_desc,
		&m_ShaderResourceView
	);

	if (FAILED(hr)) {
		NEOLOG_ERROR("Failed to create shader resource view");
	}

	std::wstring wstr(file_path);
	std::string str(wstr.begin(), wstr.end());
	NEOLOG_INFO("Successfully Loaded Texture: {} ({}x{})", str, scratch_image.GetMetadata().width, scratch_image.GetMetadata().height);
}

ID3D11ShaderResourceView* TextureResource::GetShaderResourceView() {
	return m_ShaderResourceView.Get();
}