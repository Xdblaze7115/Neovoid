#include "Shader.hpp"

// Vertex Shader
VertexShader::VertexShader(LPCWSTR shader_file) {
    HRESULT hr = D3DReadFileToBlob(shader_file, &m_Bytecode);
    if (FAILED(hr)) {
        NEOLOG_ERROR("Failed to load vertex shader bytecode");
    }
    hr = RendererContext::GetDevice()->CreateVertexShader(m_Bytecode->GetBufferPointer(), m_Bytecode->GetBufferSize(), nullptr, &m_Vertex_Shader);

    if (FAILED(hr)) {
        NEOLOG_ERROR("Failed to create vertex shader");
    }
}

void VertexShader::Bind() noexcept {
    RendererContext::GetDeviceContext()->VSSetShader(m_Vertex_Shader.Get(), nullptr, 0u);
}

void VertexShader::Unbind() noexcept {
    RendererContext::GetDeviceContext()->VSSetShader(nullptr, nullptr, 0u);
}

ID3DBlob* VertexShader::GetBytecode() {
    return m_Bytecode.Get();
}

// Pixel Shader
PixelShader::PixelShader(LPCWSTR shader_file) {
    HRESULT hr = D3DReadFileToBlob(shader_file, &m_Bytecode);
    if (FAILED(hr)) {
        NEOLOG_ERROR("Failed to load pixel shader bytecode");
    }
    hr = RendererContext::GetDevice()->CreatePixelShader(m_Bytecode->GetBufferPointer(), m_Bytecode->GetBufferSize(), nullptr, &m_Pixel_Shader);

    if (FAILED(hr)) {
        NEOLOG_ERROR("Failed to create pixel shader");
    }
}

void PixelShader::Bind() noexcept {
    RendererContext::GetDeviceContext()->PSSetShader(m_Pixel_Shader.Get(), nullptr, 0u);
}

void PixelShader::Unbind() noexcept {
    RendererContext::GetDeviceContext()->PSSetShader(nullptr, nullptr, 0u);
}

ID3DBlob* PixelShader::GetBytecode() {
    return m_Bytecode.Get();
}