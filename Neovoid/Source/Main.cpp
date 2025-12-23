#include "Logging/Logging.hpp"
#include "Backend/Backend.hpp"
#include "Window/Window.hpp"

int main() {
	Backend::Initialize();

	while (Window::WindowIsOpen()) {
		Backend::UpdateSubSystems();
		Backend::BeginFrame();
		Backend::Update();
		Backend::EndFrame();
	}
	Backend::Shutdown();
}