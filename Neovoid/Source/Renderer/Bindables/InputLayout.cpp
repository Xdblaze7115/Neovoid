#include "InputLayout.hpp"

InputLayout::InputLayout(std::vector<D3D11_INPUT_ELEMENT_DESC>& input_element_descs, ID3DBlob* vertex_shader_bytecode) {
    HRESULT hr = RendererContext::GetDevice()->CreateInputLayout(
        input_element_descs.data(),
        (UINT)input_element_descs.size(),
        vertex_shader_bytecode->GetBufferPointer(),
        vertex_shader_bytecode->GetBufferSize(),
        &m_InputLayout
    );

    if (FAILED(hr)) {
        NEOLOG_ERROR("Failed to create input layout");
    }
}
    
bool InputLayout::IsValid() {
    return m_InputLayout != nullptr;
}

void InputLayout::Bind() noexcept {
    RendererContext::GetDeviceContext()->IASetInputLayout(m_InputLayout.Get());
}

void InputLayout::Unbind() noexcept {
    RendererContext::GetDeviceContext()->IASetInputLayout(nullptr);
}