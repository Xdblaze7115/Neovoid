#pragma once
#include "Math/Vector.hpp"

class FrustumPlane {
	Vector3 Normal;
	float Offset;
};

class Frustum {
	FrustumPlane Planes[6] = {};
	Vector3 Corners[8] = {};
	Vector3 BoundsMin = Vector3(0.0f);
	Vector3 BoundsMax = Vector3(0.0f);
};