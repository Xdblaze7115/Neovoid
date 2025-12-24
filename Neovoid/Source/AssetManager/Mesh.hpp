#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "Math/Vertex.hpp"

struct Mesh {
private:
public:
	std::vector<Vertex> m_Vertices;
	std::vector<uint32_t> m_Indices;
	Mesh(std::string file_path);
};