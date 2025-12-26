#pragma once
#include "Math/Vector.hpp"

class Light {
public:
	uintptr_t m_Type;
	Vector3 m_Color;

	Light();
};