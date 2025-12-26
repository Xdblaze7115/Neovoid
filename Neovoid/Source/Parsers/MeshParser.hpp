#pragma once
#include <string>
#include "Math/Vector.hpp"
#include "Math/Vertex.hpp"

class Material {
public:
	std::string Name; // Name Of The Material
	Vector3 AmbientColor; // Color Under Ambient Light
	Vector3 DiffuseColor; // Main Surface Color
	Vector3 SpecularColor; // Highlight Color
	Vector3 EmissiveColor; // Self Illumination Color
	float SpecularExponent; // Shininess Higher = Sharper Highlights
	float OpticalDensity; // Refraction Index 1.0f = No Refraction
	float Dissolve; // Transparency 1.0f = Fully Opaque
	unsigned int IlluminationModel; // 2 = Highlight On (Specular Enabled)
};

class MeshMesh {
public:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	Material m_Material;
};

class MeshScene {
public:
	std::vector<MeshMesh> m_Meshes;
};

class MeshParser {
public:
	MeshParser();
	MeshScene ParseObjFile(std::string file_path);
};