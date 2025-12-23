#include "Topology.hpp"

Topology::Topology(D3D11_PRIMITIVE_TOPOLOGY type) {
	m_Type = type;
}

void Topology::Bind() noexcept {
	RendererContext::GetDeviceContext()->IASetPrimitiveTopology(m_Type);
}

void Topology::Unbind() noexcept {
	RendererContext::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED);
}