#include <filesystem>
#include "Mesh.hpp"
#include "Logging/Logging.hpp"
#include "Renderer/RendererContext.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

Mesh::Mesh(std::string file_path) {
	if (!std::filesystem::exists(file_path)) {
		NEOLOG_ERROR("Mesh file does not exist: {}", std::filesystem::path(file_path).string());
		return;
	}

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(file_path,
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_CalcTangentSpace |
        aiProcess_FlipUVs
    );

    if (scene == nullptr) {
        NEOLOG_ERROR(importer.GetErrorString());
        return;
    }

    for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
        const aiMesh* mesh = scene->mMeshes[m];

        // Load vertices
        m_Vertices.resize(mesh->mNumVertices);
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            Vertex& v = m_Vertices[i];
            v.Position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
            if (mesh->HasNormals())
                v.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
            if (mesh->HasTextureCoords(0))
                v.Texcoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
            else
                v.Texcoord = { 0.0f, 0.0f };
        }

        // Load indices
        m_Indices.reserve(mesh->mNumFaces * 3);
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            const aiFace& face = mesh->mFaces[i];
            m_Indices.push_back(face.mIndices[0]);
            m_Indices.push_back(face.mIndices[1]);
            m_Indices.push_back(face.mIndices[2]);
        }
    }

    NEOLOG_INFO("Successfully Loaded Mesh: {}", file_path);
}