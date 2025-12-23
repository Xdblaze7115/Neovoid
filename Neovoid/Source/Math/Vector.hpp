#pragma once
#include <cmath>
#include <limits>

struct Vector4;
struct Matrix4;

inline float PI = 3.14159265358979323846f;
inline float Infinity = std::numeric_limits<float>::infinity();

inline float Deg2Rad_Multiplier = (PI / 180.0f);
inline float Rad2Deg_Multiplier = (180.0f / PI);

inline float Deg_To_Rad(float degrees) {
    return degrees * (PI / 180.0f);
}

inline float Rad_To_Deg(float radians) {
    return radians * (180.0f / PI);
}

struct Vector2 {
    float X, Y;
};

struct Vector3 {
    float X, Y, Z;
    float Normal();
    Vector3 Normalize();
    Vector3 Cross(Vector3 other);
    float Dot(Vector3 other);
    Vector3 operator-(Vector3 other);
    Vector3 operator+(Vector3 other);
    Vector3 operator*(Vector3 other);
};