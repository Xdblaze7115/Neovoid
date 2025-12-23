#include "World.hpp"
#include "Logging/Logging.hpp"
#include "Window/WindowInput.hpp"
#include "Viewport/ViewportManager.hpp"
#include "Camera/Camera.hpp"

#include "imgui.h"
#include "Renderer/Bindables/Buffer.hpp"
#include "Renderer/Bindables/ConstantBuffer.hpp"
#include "Renderer/Bindables/InputLayout.hpp"
#include "Renderer/Bindables/Shader.hpp"
#include "Renderer/Bindables/Topology.hpp"
#include "Renderer/Drawable/Drawable.hpp"

float g_Camera_Sensitivity = 0.002f;
Vector2 g_Last_Mouse_Position = Vector2(0, 0);

namespace World {
	Camera m_Camera;

	void Initialize() {

	}

	void BeginFrame() {
		XMVECTOR position = m_Camera.GetPosition();
		XMVECTOR rotation = m_Camera.GetRotation();

		ImGui::Begin("Camera");
		ImGui::Text("Position -> %f %f %f", XMVectorGetX(position), XMVectorGetY(position), XMVectorGetZ(position));
		ImGui::Text("Rotation -> %f %f %f", XMVectorGetX(rotation), XMVectorGetY(rotation), XMVectorGetZ(rotation));
		ImGui::End();
	}

	void EndFrame() {

	}

	void Update(float delta_time) {
		Viewport* viewport = ViewportManager::GetViewportByIndex(0);
		if (WindowInput::IsKeyPressed(NEO_KEY_W)) {
			m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetForwardVector() * delta_time);
		}
		else if (WindowInput::IsKeyPressed(NEO_KEY_S)) {
			m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetForwardVector() * delta_time);
		}
		else if (WindowInput::IsKeyPressed(NEO_KEY_A)) {
			m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetRightVector() * delta_time);
		}
		else if (WindowInput::IsKeyPressed(NEO_KEY_D)) {
			m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetRightVector() * delta_time);
		}
		else if (WindowInput::IsKeyPressed(NEO_KEY_SPACE)) {
			m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetUpVector() * delta_time);
		}
		else if (WindowInput::IsKeyPressed(NEO_KEY_CONTROL)) {
			m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetUpVector() * delta_time);
		}
		if (WindowInput::IsKeyPressed(NEO_KEY_M)) {
			static bool state = false;
			state = state ? false : true;
			viewport->SetOrthographic(state);
		}

		if (WindowInput::IsMouseButtonPressed(NEO_MOUSE_BUTTON_RIGHT)) {
			Vector2 mouse_position = WindowInput::GetMousePosition();

			// Only calculate delta if we have a previous position
			if (g_Last_Mouse_Position.X != 0 && g_Last_Mouse_Position.Y != 0) {
				float delta_x = mouse_position.X - g_Last_Mouse_Position.X;
				float delta_y = mouse_position.Y - g_Last_Mouse_Position.Y;

				delta_x *= g_Camera_Sensitivity;
				delta_y *= g_Camera_Sensitivity;

				XMVECTOR rotation = m_Camera.GetRotation();
				m_Camera.SetRotation(rotation + XMVectorSet(delta_y, -delta_x, 0.0f, 0.0f));
			}
			g_Last_Mouse_Position = mouse_position;
		}
		else {
			g_Last_Mouse_Position = Vector2(0, 0);
		}
		m_Camera.Update();

		struct Vertex {
			float X, Y, Z;
			float R, G, B, A;
		};

		std::vector<Vertex> vertices = {
			// Front Face - BLUE
			{ -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
			{ -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
			{  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },
			{  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f },

			// Back Face - RED
			{  0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
			{  0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
			{ -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
			{ -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f },
		};

		std::vector<uint32_t> indices = {
			// Front Side
			0, 1, 2,
			2, 3, 0,

			// Back Side
			4, 5, 6,
			6, 7, 4,

			// Top Side
			1, 6, 5,
			5, 2, 1,

			// Bottom Side
			7, 0, 3,
			3, 4, 7,

			// Right Side
			3, 2, 5,
			5, 4, 3,

			// Left Side
			7, 6, 1,
			1, 0, 7
		};

		RendererContext::GetDeviceContext()->RSSetViewports(1, viewport->GetViewportFrame());

		auto vertex_buffer = std::make_unique<VertexBuffer>(vertices);
		vertex_buffer->Bind();

		auto vertex_shader = std::make_unique<VertexShader>(L"../Neovoid/VertexShader.cso");
		auto vertex_shader_bytecode = vertex_shader->GetBytecode();
		vertex_shader->Bind();

		auto pixel_shader = std::make_unique<PixelShader>(L"../Neovoid/PixelShader.cso");
		pixel_shader->Bind();

		auto index_buffer = std::make_unique<IndexBuffer>(indices);
		index_buffer->Bind();

		std::vector<D3D11_INPUT_ELEMENT_DESC> input_element_desc = {
			{ "POSITION", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
			{ "COLOR", 0u, DXGI_FORMAT_R32G32B32A32_FLOAT, 0u, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0u },
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

		Constant_Transform_Buffer constant_transform_buffer = {
			DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity()),
			DirectX::XMMatrixTranspose(m_Camera.GetViewMatrix()),
			DirectX::XMMatrixTranspose(viewport->GetProjectionMatrix())
		};

		auto constant_buffer = std::make_unique<VertexConstantBuffer<Constant_Transform_Buffer>>();
		constant_buffer->Update(constant_transform_buffer);
		constant_buffer->Bind();
		RendererContext::GetDeviceContext()->DrawIndexed(index_buffer->GetCount(), 0u, 0u);
	}
}