#pragma once

#ifndef CAMERA_H
#define CAMERA_H
#include <d3d11_1.h>
#include <DirectXMath.h>
#include "Transform.h"

using namespace Physics;

class Camera
{
public:
    Camera() {};
    Camera(Transform trans);
    ~Camera();

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

    void SetPosition(Vector3 pos);
    Vector3 GetPosition() { return transform.position; };
    void SetRotation(Vector3 rotation);
    Vector3 GetRotation() { return transform.rotation; };


    void LookTo(Vector3 rotation);
    void LookAt(Transform trans);
    void LookFromTrans();

    DirectX::XMFLOAT4X4 GetView() { return _view; };
    DirectX::XMFLOAT4X4 GetProjection() { return _projection; };

    void SetAspect(float aspect) { _aspect = aspect; };
    float GetAspect() { return _aspect; };
    void SetDepth(float dNear, float dFar) { _depthNear = dNear; _depthFar = dFar; };
    float GetDepthNear() { return _depthNear; };
    float GetDepthFar() { return _depthFar; };


    Transform transform;
private:
    Vector3 _upDir = Vector3(0.0f, 1.0f, 0.0f);
    DirectX::XMFLOAT4X4 _view;
    DirectX::XMFLOAT4X4 _projection;

    float _aspect = 1.6f;

    float _depthNear = 0.01f;
    float _depthFar = 100.0f;
    
};


#endif // !CAMERA_H
