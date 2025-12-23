#pragma once
#include "Bindable.hpp"

class InputLayout : public Bindable {
private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
public:
	InputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>& input_element_descs, ID3DBlob* vertex_shader_bytecode);

	bool IsValid();
	void Bind() noexcept override;
	void Unbind() noexcept override;
};