#include <filesystem>
#include "Mesh.hpp"
#include "Logging/Logging.hpp"
#include "Parsers/MeshParser.hpp"

Mesh::Mesh(std::string file_path) {
    if (!std::filesystem::exists(file_path)) {
        NEOLOG_ERROR("Mesh File Does Not Exist -> %s", std::filesystem::path(file_path).string());
        return;
    }

    MeshParser mesh_parser;
    auto scene = mesh_parser.ParseObjFile(file_path);

    unsigned int vertex_offset = 0;

    if (!scene.m_Meshes.empty()) {
        NEOLOG_INFO("Loading %d meshes from file", scene.m_Meshes.size());

        for (auto& mesh : scene.m_Meshes) {
            NEOLOG_INFO("  Mesh: %d vertices, %d indices",
                mesh.m_Vertices.size(), mesh.m_Indices.size());

            // Add vertices
            for (auto& vertex : mesh.m_Vertices) {
                m_Vertices.push_back(vertex);
            }

            // Add indices with offset
            for (auto index : mesh.m_Indices) {
                m_Indices.push_back(index + vertex_offset);
            }

            // Update offset for next mesh
            vertex_offset += mesh.m_Vertices.size();
        }
    }

    NEOLOG_INFO("Successfully Loaded Mesh -> %s (Total: %d vertices, %d indices)",
        file_path.c_str(), m_Vertices.size(), m_Indices.size());
}