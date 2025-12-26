#include <unordered_map>
#include <filesystem>
#include "MeshParser.hpp"
#include "Logging/Logging.hpp"

std::unordered_map<std::string, Material> ParseMtlFile(std::string file_path) {
    if (!std::filesystem::exists(file_path)) {
        NEOLOG_ERROR("File Does Not Exist -> %s", std::filesystem::path(file_path).string().c_str());
    }

    std::ifstream file(file_path);
    if (!file.is_open()) {
        NEOLOG_ERROR("Failed To Open File -> %s", file_path.c_str());
    }

    std::unordered_map<std::string, Material> materials;
    Material* current_material = nullptr;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream string_stream(line);
        std::string command;
        string_stream >> command;

        if (command == "newmtl") { // Name Of The Material
            std::string name;
            std::getline(string_stream, name);
            name.erase(0, name.find_first_not_of(" \t"));
            NEOLOG_INFO("Parsing Material -> %s", name.c_str());

            materials[name] = Material();
            current_material = &materials[name];
            current_material->Name = name;
            continue;
        }
        else if (command == "Ns") { // Specular Exponent - Shininess And Higher = Sharper Highlights
            float specular_exponent;
            string_stream >> specular_exponent;
            current_material->SpecularExponent = specular_exponent;
            continue;
        }
        else if (command == "Ka") { // Ambient Color - Color Under Ambient Light
            float r, g, b;
            string_stream >> r >> g >> b;
            current_material->AmbientColor = Vector3(r, g, b);
            continue;
        }
        else if (command == "Kd") { // Diffuse Color - Main Surface Color
            float r, g, b;
            string_stream >> r >> g >> b;
            current_material->DiffuseColor = Vector3(r, g, b);
            continue;
        }
        else if (command == "Ks") { // Specular Color - Highlight Color
            float r, g, b;
            string_stream >> r >> g >> b;
            current_material->SpecularColor = Vector3(r, g, b);
            continue;
        }
        else if (command == "Ke") { // Emissive Color - Self Illumination Color
            float r, g, b;
            string_stream >> r >> g >> b;
            current_material->EmissiveColor = Vector3(r, g, b);
            continue;
        }
        else if (command == "Ni") { // Optical Density - Refraction Index 1.0f = No Refraction
            float optical_density;
            string_stream >> optical_density;
            current_material->OpticalDensity = optical_density;
            continue;
        }
        else if (command == "d") { // Dissolve - Transparency 1.0f = Fully Opaque
            float dissolve;
            string_stream >> dissolve;
            current_material->Dissolve = dissolve;
            continue;
        }
        else if (command == "illum") { // Illumination Model - 2 = Highlight On (Specular Enabled)
            unsigned int illumination_model;
            string_stream >> illumination_model;
            current_material->IlluminationModel = illumination_model;
            continue;
        }
    }
    return materials;
}

MeshParser::MeshParser() {

}

MeshScene MeshParser::ParseObjFile(std::string file_path) {
	if (!std::filesystem::exists(file_path)) {
		NEOLOG_ERROR("File Does Not Exist -> %s", std::filesystem::path(file_path).string().c_str());
	}

    std::ifstream file(file_path);
    if (!file.is_open()) {
        NEOLOG_ERROR("Failed To Open File -> %s", file_path.c_str());
    }

    std::filesystem::path obj_path(file_path);
    std::filesystem::path base_directory = obj_path.parent_path();

    MeshScene mesh_scene;
    MeshMesh* current_mesh = nullptr;

    std::unordered_map<std::string, Material> materials;
    std::vector<Vector3> positions;
    std::vector<Vector2> texcoords;
    std::vector<Vector3> normals;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream string_stream(line);
        std::string command;
        string_stream >> command;

        if (command == "mtllib") {
            std::string mtl_filename;
            std::getline(string_stream, mtl_filename);
            mtl_filename.erase(0, mtl_filename.find_first_not_of(" \t"));

            std::filesystem::path mtl_full_path = base_directory / mtl_filename;
            NEOLOG_INFO("Loading MTL: %s", mtl_full_path.string().c_str());
            materials = ParseMtlFile(mtl_full_path.string());
            continue;
        }
        else if (command == "usemtl") {
            std::string material_name;
            std::getline(string_stream, material_name);
            material_name.erase(0, material_name.find_first_not_of(" \t"));
            NEOLOG_INFO("Using Material -> %s", material_name.c_str());

            if (materials.find(material_name) != materials.end()) {
                current_mesh->m_Material = materials[material_name];
            }
            continue;
        }
        else if (command == "o") {
            std::string objectname;
            std::getline(string_stream, objectname);
            objectname.erase(0, objectname.find_first_not_of(" \t"));
            NEOLOG_INFO("Parsing Mesh -> %s", objectname.c_str());

            mesh_scene.m_Meshes.emplace_back();
            current_mesh = &mesh_scene.m_Meshes.back();
            continue;
        }
        else if (command == "v") {
            float x, y, z;
            if (string_stream >> x >> y >> z) {
                positions.push_back(Vector3(x, y, z));
            }
            continue;
        }
        else if (command == "vt") {
            float u, v;
            if (string_stream >> u >> v) {
                v = 1.0f - v;
                texcoords.push_back(Vector2(u, v));
            }
            continue;
        }
        else if (command == "vn") {
            float x, y, z;
            if (string_stream >> x >> y >> z) {
                normals.push_back(Vector3(x, y, z));
            }
            continue;
        }
        else if (command == "f") {
            std::string token;
            std::vector<int> vIndices, vtIndices, vnIndices;

            while (string_stream >> token) {
                int v_idx = -1, vt_idx = -1, vn_idx = -1;

                std::replace(token.begin(), token.end(), '/', ' ');
                std::istringstream token_stream(token);

                std::string v_str, vt_str, vn_str;
                token_stream >> v_str >> vt_str >> vn_str;

                if (!v_str.empty()) v_idx = std::stoi(v_str) - 1;
                if (!vt_str.empty()) vt_idx = std::stoi(vt_str) - 1;
                if (!vn_str.empty()) vn_idx = std::stoi(vn_str) - 1;

                vIndices.push_back(v_idx);
                vtIndices.push_back(vt_idx);
                vnIndices.push_back(vn_idx);
            }

            if (vIndices.size() >= 3) {
                if (vIndices.size() == 4) {
                    for (int tri = 0; tri < 2; tri++) {
                        int tri_indices[3];
                        if (tri == 0) {
                            tri_indices[0] = 0; tri_indices[1] = 1; tri_indices[2] = 2;
                        }
                        else {
                            tri_indices[0] = 0; tri_indices[1] = 2; tri_indices[2] = 3;
                        }

                        for (int i = 0; i < 3; i++) {
                            int idx = tri_indices[i];
                            Vertex vertex;

                            if (vIndices[idx] >= 0 && vIndices[idx] < positions.size()) {
                                vertex.Position = positions[vIndices[idx]];
                            }

                            if (vtIndices[idx] >= 0 && vtIndices[idx] < texcoords.size()) {
                                vertex.Texcoord = texcoords[vtIndices[idx]];
                            }
                            else {
                                vertex.Texcoord = Vector2(0.0f, 0.0f);
                            }

                            if (vnIndices[idx] >= 0 && vnIndices[idx] < normals.size()) {
                                vertex.Normal = normals[vnIndices[idx]];
                            }
                            else {
                                vertex.Normal = Vector3(0.0f, 1.0f, 0.0f);
                            }

                            current_mesh->m_Vertices.push_back(vertex);
                            current_mesh->m_Indices.push_back(current_mesh->m_Vertices.size() - 1);
                        }
                    }
                }
                else if (vIndices.size() == 3) {
                    for (int i = 0; i < 3; i++) {
                        Vertex vertex;

                        if (vIndices[i] >= 0 && vIndices[i] < positions.size()) {
                            vertex.Position = positions[vIndices[i]];
                        }

                        if (vtIndices[i] >= 0 && vtIndices[i] < texcoords.size()) {
                            vertex.Texcoord = texcoords[vtIndices[i]];
                        }
                        else {
                            vertex.Texcoord = Vector2(0.0f, 0.0f);
                        }

                        if (vnIndices[i] >= 0 && vnIndices[i] < normals.size()) {
                            vertex.Normal = normals[vnIndices[i]];
                        }
                        else {
                            vertex.Normal = Vector3(0.0f, 1.0f, 0.0f);
                        }

                        current_mesh->m_Vertices.push_back(vertex);
                        current_mesh->m_Indices.push_back(current_mesh->m_Vertices.size() - 1);
                    }
                }
            }
            continue;
        }
    }
    return mesh_scene; // Return the constructed mesh here yes
}