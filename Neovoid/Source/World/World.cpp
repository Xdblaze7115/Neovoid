#include "World.hpp"
#include "Logging/Logging.hpp"
#include "Window/WindowInput.hpp"
#include "Viewport/ViewportManager.hpp"
#include "Game/Game.hpp"

#include "imgui.h"
#include "Renderer/Bindables/Buffer.hpp"
#include "Renderer/Bindables/ConstantBuffer.hpp"
#include "Renderer/Bindables/InputLayout.hpp"
#include "Renderer/Bindables/Shader.hpp"
#include "Renderer/Bindables/Topology.hpp"
#include "Renderer/Bindables/Texture.hpp"
#include "AssetManager/AssetManager.hpp"

namespace World {
	void Initialize() {

	}

	void BeginFrame() {
		auto camera = Game::GetLocalPlayer()->GetCamera();
		XMVECTOR position = camera->GetPosition();
		XMVECTOR rotation = camera->GetRotation();

		ImGui::Begin("Camera");
		ImGui::Text("Position -> %f %f %f", XMVectorGetX(position), XMVectorGetY(position), XMVectorGetZ(position));
		ImGui::Text("Rotation -> %f %f %f", XMVectorGetX(rotation), XMVectorGetY(rotation), XMVectorGetZ(rotation));
		ImGui::End();
	}

	void EndFrame() {

	}

	void Update(float delta_time) {
		Viewport* viewport = ViewportManager::GetViewportByIndex(0);
		if (WindowInput::IsKeyPressed(NEO_KEY_M)) {
			static bool state = false;
			state = state ? false : true;
			viewport->SetOrthographic(state);
		}

		/*struct Vertex {
			float X, Y, Z;
			float U, V;
		};

		std::vector<Vertex> vertices = {
			// Front face
			{ -0.5f, -0.5f, -0.5f, 0.0f, 1.0f },  // Bottom-left
			{ -0.5f,  0.5f, -0.5f, 0.0f, 0.0f },  // Top-left
			{  0.5f,  0.5f, -0.5f, 1.0f, 0.0f },  // Top-right
			{  0.5f, -0.5f, -0.5f, 1.0f, 1.0f },  // Bottom-right

			// Back face  
			{  0.5f, -0.5f,  0.5f, 0.0f, 1.0f },  // Bottom-left
			{  0.5f,  0.5f,  0.5f, 0.0f, 0.0f },  // Top-left
			{ -0.5f,  0.5f,  0.5f, 1.0f, 0.0f },  // Top-right
			{ -0.5f, -0.5f,  0.5f, 1.0f, 1.0f },  // Bottom-right

			// Top face
			{ -0.5f,  0.5f, -0.5f, 0.0f, 1.0f },  // Front-left
			{ -0.5f,  0.5f,  0.5f, 0.0f, 0.0f },  // Back-left
			{  0.5f,  0.5f,  0.5f, 1.0f, 0.0f },  // Back-right
			{  0.5f,  0.5f, -0.5f, 1.0f, 1.0f },  // Front-right

			// Bottom face
			{ -0.5f, -0.5f,  0.5f, 0.0f, 1.0f },  // Back-left
			{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f },  // Front-left
			{  0.5f, -0.5f, -0.5f, 1.0f, 0.0f },  // Front-right
			{  0.5f, -0.5f,  0.5f, 1.0f, 1.0f },  // Back-right

			// Right face
			{  0.5f, -0.5f, -0.5f, 0.0f, 1.0f },  // Front-bottom
			{  0.5f,  0.5f, -0.5f, 0.0f, 0.0f },  // Front-top
			{  0.5f,  0.5f,  0.5f, 1.0f, 0.0f },  // Back-top
			{  0.5f, -0.5f,  0.5f, 1.0f, 1.0f },  // Back-bottom

			// Left face
			{ -0.5f, -0.5f,  0.5f, 0.0f, 1.0f },  // Back-bottom
			{ -0.5f,  0.5f,  0.5f, 0.0f, 0.0f },  // Back-top
			{ -0.5f,  0.5f, -0.5f, 1.0f, 0.0f },  // Front-top
			{ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f }   // Front-bottom
		};

		std::vector<uint32_t> indices = {
			// Front face (0-3)
			0, 1, 2,  0, 2, 3,

			// Back face (4-7)
			4, 5, 6,  4, 6, 7,

			// Top face (8-11)
			8, 9, 10, 8, 10, 11,

			// Bottom face (12-15)
			12, 13, 14, 12, 14, 15,

			// Right face (16-19)
			16, 17, 18, 16, 18, 19,

			// Left face (20-23)
			20, 21, 22, 20, 22, 23
		};*/

		RendererContext::GetDeviceContext()->RSSetViewports(1, viewport->GetViewportFrame());

		auto mesh = AssetManager::CreateMeshFromFile(L"Resources/Meshes/teapot.obj");

		auto vertex_buffer = std::make_unique<VertexBuffer>(mesh->m_Vertices);
		vertex_buffer->Bind();

		auto vertex_shader = std::make_unique<VertexShader>(L"../Neovoid/VertexShader.cso");
		auto vertex_shader_bytecode = vertex_shader->GetBytecode();
		vertex_shader->Bind();

		auto pixel_shader = std::make_unique<PixelShader>(L"../Neovoid/PixelShader.cso");
		pixel_shader->Bind();

		auto wood_texture = AssetManager::CreateTextureFromFile(L"Resources/Textures/brick.png");
		auto texture = std::make_unique<Texture>(wood_texture);
		texture->Bind();

		auto index_buffer = std::make_unique<IndexBuffer>(mesh->m_Indices);
		index_buffer->Bind();

		std::vector<D3D11_INPUT_ELEMENT_DESC> input_element_desc = {
			{ "POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
			{ "NORMAL", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
			{ "TEXCOORD", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 24u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
		};
		auto input_layout = std::make_unique<InputLayout>(input_element_desc, vertex_shader_bytecode);
		input_layout->Bind();

		auto topology = std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		topology->Bind();

		struct Constant_Transform_Buffer {
			DirectX::XMMATRIX Model;
			DirectX::XMMATRIX View;
			DirectX::XMMATRIX Projection;
		};

		auto camera = Game::GetLocalPlayer()->GetCamera();
		Constant_Transform_Buffer constant_transform_buffer = {
			DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity()),
			DirectX::XMMatrixTranspose(camera->GetViewMatrix()),
			DirectX::XMMatrixTranspose(viewport->GetProjectionMatrix())
		};

		auto constant_buffer = std::make_unique<VertexConstantBuffer<Constant_Transform_Buffer>>();
		constant_buffer->Update(constant_transform_buffer);
		constant_buffer->Bind();
		RendererContext::GetDeviceContext()->DrawIndexed(index_buffer->GetCount(), 0u, 0u);
	}
}