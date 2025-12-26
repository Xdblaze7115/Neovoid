#pragma once

class Material {
public:
    float shininess = 256.0f; // Higher = sharper specular (more metallic)
    float specular_power = 2.0f; // Higher = brighter specular
    float ambient_strength = 0.1f; // Lower = darker ambient
    float diffuse_strength = 0.6f; // Lower = less diffuse
};