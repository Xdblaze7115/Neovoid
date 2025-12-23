#include "Imgui.hpp"
#include "Logging/Logging.hpp"
#include "Renderer/RendererContext.hpp"

namespace Imgui {
	void Initialize() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
        RendererContext::InitializeImgui();
	}

	void Shutdown() {
        RendererContext::ShutdownImgui();
        ImGui::DestroyContext();
	}

    void BeginFrame() {
        RendererContext::BeginImguiFrame();
        ImGui::NewFrame();
    }

    void EndFrame() {
        ImGui::Render();
        RendererContext::EndImguiFrame();
    }

    void Update() {
        static bool show = true;
        static char text[128] = "";
        if (ImGui::Begin("Test Imgui Menu", &show)) {
            ImGui::Text("Engine Made By Xdblaze");
            ImGui::InputText("hi", text, IM_ARRAYSIZE(text));
            ImGui::Text("Text Entered -> %s", text);
        }
        ImGui::End();
    }
}