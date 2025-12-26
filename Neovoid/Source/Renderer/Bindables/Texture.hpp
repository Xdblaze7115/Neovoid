#pragma once
#include "Nodes/Texture/TextureResource.hpp"
#include "Bindable.hpp"

class Texture : public Bindable {
private:
	UINT m_StartSlot = 0u;
	ID3D11ShaderResourceView* m_ShaderResourceView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_SamplerState;
public:
	Texture(TextureResource* texture_resource, UINT start_slot = 0);

	void Bind() noexcept override;
	void Unbind() noexcept override;
};