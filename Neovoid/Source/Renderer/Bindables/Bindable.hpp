#pragma once
#include "Logging/Logging.hpp"
#include "Renderer/RendererContext.hpp"

class Bindable {
public:
	virtual ~Bindable() = default;
	virtual void Bind() noexcept = 0;
	virtual void Unbind() noexcept = 0;
};