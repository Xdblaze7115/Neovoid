#include <cmath>
#include "Vector.hpp"

float Vector3::Normal() {
    return sqrtf(
        X * X +
        Y * Y +
        Z * Z
    );
}

Vector3 Vector3::Normalize() {
    float normal = Normal();
    return Vector3{
        X / normal,
        Y / normal,
        Z / normal
    };
}

Vector3 Vector3::Cross(Vector3 other) {
    return Vector3(
        Y * other.Z - Z * other.Y,
        Z * other.X - X * other.Z,
        X * other.Y - Y * other.X
    );
}

float Vector3::Dot(Vector3 other) {
    return
        X * other.X +
        Y * other.Y +
        Z * other.Z;
}

Vector3 Vector3::operator-(Vector3 other) {
    return Vector3{ X - other.X, Y - other.Y, Z - other.Z };
}

Vector3 Vector3::operator+(Vector3 other) {
    return Vector3{ X + other.X, Y + other.Y, Z + other.Z };
}

Vector3 Vector3::operator*(Vector3 other) {
    return Vector3{ X * other.X, Y * other.Y, Z * other.Z };
}