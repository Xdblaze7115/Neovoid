#pragma once
#include "Bindable.hpp"

class Topology : public Bindable {
private:
	D3D11_PRIMITIVE_TOPOLOGY m_Type;
public:
	Topology(D3D11_PRIMITIVE_TOPOLOGY type);

	void Bind() noexcept override;;
	void Unbind() noexcept override;;
};