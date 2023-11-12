#pragma once

#ifndef CAMERA_H
#define CAMERA_H
#include <d3d11_1.h>
#include <DirectXMath.h>
#include "Transform.h"

using namespace DirectX;

class Camera
{
public:
    Camera() {};
    Camera(Transform trans);
    ~Camera();

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

    void SetPosition(XMFLOAT3 pos);
    XMFLOAT3 GetPosition() { return transform.position; };
    void SetRotation(XMFLOAT3 rotation);
    XMFLOAT3 GetRotation() { return transform.rotation; };


    void LookTo(XMFLOAT3 rotation);
    void LookAt(Transform trans);
    void LookFromTrans();

    XMFLOAT4X4 GetView() { return _view; };
    XMFLOAT4X4 GetProjection() { return _projection; };

    void SetAspect(float aspect) { _aspect = aspect; };
    void SetDepth(float dNear, float dFar) { _depthNear = dNear; _depthFar = dFar; };


    Transform transform;
private:
    XMFLOAT3 _upDir = XMFLOAT3(0.0f, 1.0f, 0.0f);
    XMFLOAT4X4 _view;
    XMFLOAT4X4 _projection;

    float _aspect = 1.6f;

    float _depthNear = 0.01f;
    float _depthFar = 100.0f;
    
};


#endif // !CAMERA_H
