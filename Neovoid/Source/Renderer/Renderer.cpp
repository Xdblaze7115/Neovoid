#include "Renderer.hpp"
#include "RendererContext.hpp"

namespace Renderer {
	//std::vector<Instance> m_Instances;

	void Initialize() {
		RendererContext::Initialize();
	}

	void BeginFrame() {
		RendererContext::Clear(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void EndFrame() {
		RendererContext::Present();
	}

	void Update() {

	}

	void SubmitInstance() {

	}
};