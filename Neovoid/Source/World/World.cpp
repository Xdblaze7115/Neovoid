#include "World.hpp"
#include "Logging/Logging.hpp"
#include "Window/WindowInput.hpp"
#include "Viewport/ViewportManager.hpp"
#include "Game/Game.hpp"
#include "Viewport/Viewport.hpp"
#include "Nodes/Light/Light.hpp"

#include "imgui.h"
#include "Renderer/Bindables/Buffer.hpp"
#include "Renderer/Bindables/ConstantBuffer.hpp"
#include "Renderer/Bindables/InputLayout.hpp"
#include "Renderer/Bindables/Shader.hpp"
#include "Renderer/Bindables/Topology.hpp"
#include "Renderer/Bindables/Texture.hpp"
#include "AssetManager/AssetManager.hpp"

namespace World {
	Viewport g_viewport;
	std::vector<Light> g_Lights;

	void Initialize() {
		Vector2 window_size = Window::GetSize();
		g_viewport = Viewport(0, Vector2(0, 0), window_size);
	}

	void BeginFrame() {
		auto camera = Game::GetLocalPlayer()->GetCamera();
		XMVECTOR position = camera->GetPosition();
		XMVECTOR rotation = camera->GetRotation();

		ImGui::Begin("Camera");
		ImGui::Text("Position: X:%.3f Y:%.3f Z:%.3f", XMVectorGetX(position), XMVectorGetY(position), XMVectorGetZ(position));
		ImGui::Text("Rotation: X:%.f Y:%.f Z:%.f", XMConvertToDegrees(XMVectorGetX(rotation)), XMConvertToDegrees(XMVectorGetY(rotation)), XMConvertToDegrees(XMVectorGetZ(rotation)));
		ImGui::End();
	}

	void EndFrame() {

	}

	void Update(float delta_time) {
		g_viewport.Update();
		g_viewport.SetSize(Window::GetSize());
		if (WindowInput::IsKeyPressed(NEO_KEY_M)) {
			static bool state = false;
			state = state ? false : true;
			g_viewport.SetOrthographic(state);
		}

		/*std::vector<Vertex> vertices = {
			// Front face
			{ -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f },  // Bottom-left
			{ -0.5f,  0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f },  // Top-left
			{  0.5f,  0.5f, -0.5f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f },  // Top-right
			{  0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f },  // Bottom-right

			// Back face  
			{  0.5f, -0.5f,  0.5f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f },  // Bottom-left
			{  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f },  // Top-left
			{ -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f },  // Top-right
			{ -0.5f, -0.5f,  0.5f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f },  // Bottom-right

			// Top face
			{ -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f },  // Front-left
			{ -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f },  // Back-left
			{  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f },  // Back-right
			{  0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f },  // Front-right

			// Bottom face
			{ -0.5f, -0.5f,  0.5f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f },  // Back-left
			{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f },  // Front-left
			{  0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f },  // Front-right
			{  0.5f, -0.5f,  0.5f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f },  // Back-right

			// Right face
			{  0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f },  // Front-bottom
			{  0.5f,  0.5f, -0.5f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f },  // Front-top
			{  0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f },  // Back-top
			{  0.5f, -0.5f,  0.5f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f },  // Back-bottom

			// Left face
			{ -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f },  // Back-bottom
			{ -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f },  // Back-top
			{ -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f },  // Front-top
			{ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f }   // Front-bottom
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

		RendererContext::GetDeviceContext()->RSSetViewports(1, g_viewport.GetViewportFrame());

		{
			auto mesh = AssetManager::CreateMeshFromFile(L"Resources/Meshes/statue.obj");

			auto vertex_buffer = std::make_unique<VertexBuffer>(mesh->m_Vertices);
			vertex_buffer->Bind();

			auto vertex_shader = std::make_unique<VertexShader>(L"VertexShader.cso");
			auto vertex_shader_bytecode = vertex_shader->GetBytecode();
			vertex_shader->Bind();

			auto pixel_shader = std::make_unique<PixelShader>(L"PixelShader.cso");
			pixel_shader->Bind();

			auto wood_texture = AssetManager::CreateTextureFromFile(L"Resources/Textures/wood.jpg");
			auto texture = std::make_unique<Texture>(wood_texture);
			texture->Bind();

			auto index_buffer = std::make_unique<IndexBuffer>(mesh->m_Indices);
			index_buffer->Bind();

			std::vector<D3D11_INPUT_ELEMENT_DESC> input_element_desc = {
				{ "POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
				{ "TEXCOORD", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
				{ "NORMAL", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 20u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
			};
			auto input_layout = std::make_unique<InputLayout>(input_element_desc, vertex_shader_bytecode);
			input_layout->Bind();

			auto topology = std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			topology->Bind();

			struct Constant_Transform_Buffer {
				DirectX::XMMATRIX Model;
				DirectX::XMMATRIX View;
				DirectX::XMMATRIX Projection;
				DirectX::XMVECTOR CameraPosition;
				DirectX::XMVECTOR LightDirection;
			};

			auto camera = Game::GetLocalPlayer()->GetCamera();

			static float light_time = 0.0f;
			light_time += 0.001f;
			DirectX::XMMATRIX light_rotation_matrix = DirectX::XMMatrixRotationY(light_time);
			DirectX::XMVECTOR light_direction = DirectX::XMVector3TransformNormal(
				DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
				light_rotation_matrix
			);
			light_direction = DirectX::XMVector3Normalize(light_direction);

			float scale = 1.0f;
			Constant_Transform_Buffer constant_transform_buffer = {
				DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(scale, scale, scale)),
				DirectX::XMMatrixTranspose(camera->GetViewMatrix()),
				DirectX::XMMatrixTranspose(g_viewport.GetProjectionMatrix()),
				camera->GetPosition(),
				light_direction
			};

			auto vertex_constant_buffer = std::make_unique<VertexConstantBuffer<Constant_Transform_Buffer>>();
			vertex_constant_buffer->Update(constant_transform_buffer);
			vertex_constant_buffer->Bind();

			auto pixel_constant_buffer = std::make_unique<PixelConstantBuffer<Constant_Transform_Buffer>>();
			pixel_constant_buffer->Update(constant_transform_buffer);
			pixel_constant_buffer->Bind();

			RendererContext::GetDeviceContext()->DrawIndexed(index_buffer->GetCount(), 0u, 0u);
		}

		{
			auto mesh = AssetManager::CreateMeshFromFile(L"Resources/Meshes/marble_bust_01_4k.obj");

			auto vertex_buffer = std::make_unique<VertexBuffer>(mesh->m_Vertices);
			vertex_buffer->Bind();

			auto vertex_shader = std::make_unique<VertexShader>(L"VertexShader.cso");
			auto vertex_shader_bytecode = vertex_shader->GetBytecode();
			vertex_shader->Bind();

			auto pixel_shader = std::make_unique<PixelShader>(L"PixelShader.cso");
			pixel_shader->Bind();

			auto wood_texture = AssetManager::CreateTextureFromFile(L"Resources/Textures/marble_bust_01_diff_4k.jpg");
			auto texture = std::make_unique<Texture>(wood_texture);
			texture->Bind();

			auto index_buffer = std::make_unique<IndexBuffer>(mesh->m_Indices);
			index_buffer->Bind();

			std::vector<D3D11_INPUT_ELEMENT_DESC> input_element_desc = {
				{ "POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
				{ "TEXCOORD", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
				{ "NORMAL", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 20u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
			};
			auto input_layout = std::make_unique<InputLayout>(input_element_desc, vertex_shader_bytecode);
			input_layout->Bind();

			auto topology = std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			topology->Bind();

			struct Constant_Transform_Buffer {
				DirectX::XMMATRIX Model;
				DirectX::XMMATRIX View;
				DirectX::XMMATRIX Projection;
				DirectX::XMVECTOR CameraPosition;
				DirectX::XMVECTOR LightDirection;
			};

			auto camera = Game::GetLocalPlayer()->GetCamera();

			static float light_time = 0.0f;
			light_time += 0.001f;
			DirectX::XMMATRIX light_rotation_matrix = DirectX::XMMatrixRotationY(light_time);
			DirectX::XMVECTOR light_direction = DirectX::XMVector3TransformNormal(
				DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
				light_rotation_matrix
			);
			light_direction = DirectX::XMVector3Normalize(light_direction);

			float scale = 1.0f;
			Constant_Transform_Buffer constant_transform_buffer = {
				DirectX::XMMatrixTranspose(
					DirectX::XMMatrixScaling(scale, scale, scale)*
					DirectX::XMMatrixTranslation(1.0f, 0.0f, 0.0f)
				),
				DirectX::XMMatrixTranspose(camera->GetViewMatrix()),
				DirectX::XMMatrixTranspose(g_viewport.GetProjectionMatrix()),
				camera->GetPosition(),
				light_direction
			};

			auto vertex_constant_buffer = std::make_unique<VertexConstantBuffer<Constant_Transform_Buffer>>();
			vertex_constant_buffer->Update(constant_transform_buffer);
			vertex_constant_buffer->Bind();

			auto pixel_constant_buffer = std::make_unique<PixelConstantBuffer<Constant_Transform_Buffer>>();
			pixel_constant_buffer->Update(constant_transform_buffer);
			pixel_constant_buffer->Bind();

			RendererContext::GetDeviceContext()->DrawIndexed(index_buffer->GetCount(), 0u, 0u);
		}

		{
			auto mesh = AssetManager::CreateMeshFromFile(L"Resources/Meshes/sphere.obj");

			auto vertex_buffer = std::make_unique<VertexBuffer>(mesh->m_Vertices);
			vertex_buffer->Bind();

			auto vertex_shader = std::make_unique<VertexShader>(L"VertexShader.cso");
			auto vertex_shader_bytecode = vertex_shader->GetBytecode();
			vertex_shader->Bind();

			auto pixel_shader = std::make_unique<PixelShader>(L"SkyboxShader.cso");
			pixel_shader->Bind();

			auto wood_texture = AssetManager::CreateTextureFromFile(L"Resources/Textures/kloofendal_48d_partly_cloudy_puresky.jpg");
			auto texture = std::make_unique<Texture>(wood_texture);
			texture->Bind();

			auto index_buffer = std::make_unique<IndexBuffer>(mesh->m_Indices);
			index_buffer->Bind();

			std::vector<D3D11_INPUT_ELEMENT_DESC> input_element_desc = {
				{ "POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
				{ "TEXCOORD", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
				{ "NORMAL", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 20u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
			};
			auto input_layout = std::make_unique<InputLayout>(input_element_desc, vertex_shader_bytecode);
			input_layout->Bind();

			auto topology = std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			topology->Bind();

			struct Constant_Transform_Buffer {
				DirectX::XMMATRIX Model;
				DirectX::XMMATRIX View;
				DirectX::XMMATRIX Projection;
				DirectX::XMVECTOR CameraPosition;
				DirectX::XMVECTOR LightDirection;
			};

			auto camera = Game::GetLocalPlayer()->GetCamera();

			DirectX::XMMATRIX light_rotation_matrix = DirectX::XMMatrixRotationY(0.0f);
			DirectX::XMVECTOR light_direction = DirectX::XMVector3TransformNormal(
				DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
				light_rotation_matrix
			);
			light_direction = DirectX::XMVector3Normalize(light_direction);

			float scale = 256.0f; // Far Plane of CAMERA NOT VIEWPORT SO MOVE THE FRUSTUM (Projection Matrix) BACK INTO THE CAMERA CLASS!!!
			Constant_Transform_Buffer constant_transform_buffer = {
				DirectX::XMMatrixTranspose(
					DirectX::XMMatrixScaling(scale, scale, scale) *
					DirectX::XMMatrixTranslationFromVector(camera->GetPosition())
				),
				DirectX::XMMatrixTranspose(camera->GetViewMatrix()),
				DirectX::XMMatrixTranspose(g_viewport.GetProjectionMatrix()),
				camera->GetPosition(),
				light_direction
			};

			auto vertex_constant_buffer = std::make_unique<VertexConstantBuffer<Constant_Transform_Buffer>>();
			vertex_constant_buffer->Update(constant_transform_buffer);
			vertex_constant_buffer->Bind();

			auto pixel_constant_buffer = std::make_unique<PixelConstantBuffer<Constant_Transform_Buffer>>();
			pixel_constant_buffer->Update(constant_transform_buffer);
			pixel_constant_buffer->Bind();

			RendererContext::GetDeviceContext()->DrawIndexed(index_buffer->GetCount(), 0u, 0u);
		}
	}
}