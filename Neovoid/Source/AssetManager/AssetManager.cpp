#include <string>
#include <unordered_map>
#include <filesystem>
#include "AssetManager.hpp"

namespace AssetManager {
	std::unordered_map<std::string, Mesh> m_Meshes;
    std::unordered_map<std::string, TextureResource> m_Textures;

	void Initialize() {

	}

    TextureResource* CreateTextureFromFile(const wchar_t* file_path) {
		std::filesystem::path path(file_path);
		std::wstring full_path = std::filesystem::absolute(path).wstring();

        std::string key = path.filename().string();
        auto it = m_Textures.find(key);
        if (it != m_Textures.end()) {
            return &it->second;
        }

        auto result = m_Textures.emplace(key, TextureResource(full_path.c_str()));
        if (result.second) {
            return &result.first->second;
        }
        else {
            return nullptr;
        }
	}

    Mesh* CreateMeshFromFile(const wchar_t* file_path) {
        std::filesystem::path path(file_path);
        std::string full_path = std::filesystem::absolute(path).string();

        std::string key = path.filename().string();
        auto it = m_Meshes.find(key);
        if (it != m_Meshes.end()) {
            return &it->second;
        }

        auto result = m_Meshes.emplace(key, Mesh(full_path));
        if (result.second) {
            return &result.first->second;
        }
        else {
            return nullptr;
        }
    }
}