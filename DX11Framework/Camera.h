#pragma once

#ifndef CAMERA_H
#define CAMERA_H
#include <d3d11_1.h>
#include <DirectXMath.h>

using namespace DirectX;

class Camera
{
public:
    Camera(XMFLOAT3X3 EyeAtUp);
    ~Camera();

    void UpdateViewMatrix();

    void SetPosition(XMFLOAT3 pos);
    XMFLOAT3 GetPosition() { return Eye; };
    void SetAt(XMFLOAT3 at);
    XMFLOAT3 GetAt() { return At; };
    void SetUp(XMFLOAT3 up);
    XMFLOAT3 GetUp() { return Up; };

    void LookAt(XMFLOAT3 pos);
    XMFLOAT4X4 GetView() { return _view; };
private:
    XMFLOAT3 Eye;
    XMFLOAT3 At;
    XMFLOAT3 Up;

    XMFLOAT4X4 _view;

};


#endif // !CAMERA_H
