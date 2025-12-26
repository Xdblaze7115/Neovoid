#pragma once
#include <string>
#include <vector>
#include <d3d11.h>
#include <wrl/client.h>
#include "Math/Vertex.hpp"

class Mesh {
private:
public:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

	Mesh(std::string file_path);
};