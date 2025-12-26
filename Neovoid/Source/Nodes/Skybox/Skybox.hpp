#pragma once
#include "Nodes/Mesh/Mesh.hpp"
#include "Nodes/Texture/TextureResource.hpp"

class Skybox {
public:
	Mesh* m_Mesh;
	TextureResource* m_Texture;
};