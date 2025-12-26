#pragma once
#include <string>
#include <d3d11.h>
#include <wrl/client.h>

class TextureResource {
private:
	Microsoft::WRL::ComPtr<ID3D11Resource> m_Texture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView = nullptr;
public:
	TextureResource(const wchar_t* file_path);
	ID3D11ShaderResourceView* GetShaderResourceView();
};