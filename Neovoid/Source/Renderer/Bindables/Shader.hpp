#pragma once
#include "Bindable.hpp"

class VertexShader : public Bindable {
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_Vertex_Shader;
	Microsoft::WRL::ComPtr<ID3DBlob> m_Bytecode;
public:
	VertexShader(LPCWSTR shader_file);

	void Bind() noexcept override;
	void Unbind() noexcept override;

	ID3DBlob* GetBytecode();
};

class PixelShader : public Bindable {
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_Pixel_Shader;
	Microsoft::WRL::ComPtr<ID3DBlob> m_Bytecode;
public:
	PixelShader(LPCWSTR shader_file);

	void Bind() noexcept override;
	void Unbind() noexcept override;

	ID3DBlob* GetBytecode();
};