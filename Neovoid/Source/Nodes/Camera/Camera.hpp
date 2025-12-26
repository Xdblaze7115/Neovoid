#pragma once
#include <DirectXMath.h>
#include "Math/Vector.hpp"
#include "BackEnd/BackEnd.hpp"
using namespace DirectX;

class Camera { // Basically moves the "world" around you
private:
    XMVECTOR Forward = XMVectorSet(0, 0, 1, 0);
    XMVECTOR Up = XMVectorSet(0, 1, 0, 0);
    XMVECTOR Right = XMVectorSet(1, 0, 0, 0);

    XMVECTOR Position = XMVectorSet(0, 0, 0, 0); // X, Y, Z Used By Matrix
    XMVECTOR Rotation = XMVectorSet(0, 0, 0, 0); // Roll, Pitch, Yaw

    XMMATRIX View_Matrix = XMMatrixIdentity(); // World To Camera
    XMMATRIX Inverse_View_Matrix = XMMatrixIdentity(); // Camera To World
public:
    void Update();
    void LookAt(XMVECTOR target);
    void SetPosition(XMVECTOR position);
    void SetRotation(XMVECTOR rotation);

    XMMATRIX GetViewMatrix();
    XMMATRIX GetInverseViewMatrix();
    XMVECTOR GetForwardVector();
    XMVECTOR GetUpVector();
    XMVECTOR GetRightVector();
    XMVECTOR GetPosition();
    XMVECTOR GetRotation();
};