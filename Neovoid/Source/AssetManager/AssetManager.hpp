#pragma once
#include "Nodes/Mesh/Mesh.hpp"
#include "Nodes/Texture/TextureResource.hpp"

namespace AssetManager {
	void Initialize();
	TextureResource* CreateTextureFromFile(const wchar_t* file_path);
	Mesh* CreateMeshFromFile(const wchar_t* file_path);
}