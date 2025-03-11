#pragma once

#ifndef CAMERA_H
#define CAMERA_H
#include <d3d11_1.h>
#include <DirectXMath.h>
#include "Transform.h"
#include "Debug.h"
#ifndef USE_DIRECTXTK_MATH
using namespace Physics;
#else
using namespace DirectX::SimpleMath;
#endif // !USE_DIRECTXTK_MATH


class Camera
{
public:
    Camera() {};
    Camera(Transform trans);
    ~Camera();

    void PostInit() {
        lookAtTrans = transform;
        lookAtTrans.position *= -1; // Initial inverse position.
    };

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

    void SetPosition(Vector3 pos);
    Vector3 GetPosition() { return transform.position; };
    void SetLookAtTrans(const Vector3& toRotateTo) {
        // This is rotates the point of LookAt around 0.
        const float rotation = cosf(toRotateTo.z);
        lookAtTrans.position.x = rotation * sinf(toRotateTo.y);
        lookAtTrans.position.y = sin(toRotateTo.z);
        lookAtTrans.position.z = rotation * cosf(toRotateTo.y);

        // Update the right direction
        transform.right = lookAtTrans.position.Cross(transform.up);
        transform.right.Normalize();
        lookDir = toRotateTo;
    };

    void LookTo(Quaternion rotation);
    void LookAt(Transform trans);
    void LookFromTrans();
    void LookFlyCam();

    DirectX::XMFLOAT4X4 GetView() { return _view; };
    DirectX::XMFLOAT4X4 GetProjection() { return _projection; };

    void SetAspect(float aspect) { _aspect = aspect; }
    float GetAspect() { return _aspect; };
    void SetDepth(float dNear, float dFar) { 
        _depthNear = dNear;
        _depthNear = max(dNear, 0.001f);
        _depthFar = dFar;
        _depthNear = min(dFar, 2000.0f);
        _depthNear = min(dNear, dFar);

        //DebugPrintF("Near Depth: %f | Far Depth: %f\n", _depthNear, _depthFar);
    }

    float GetDepthNear() { return _depthNear; };
    float GetDepthFar() { return _depthFar; };

    Transform transform;
    Transform lookAtTrans;
    Vector3 lookDir;
    bool flyCam = 0;
private:
    Vector3 _upDir = Vector3(0.0f, 1.0f, 0.0f);

    DirectX::XMFLOAT4X4 _view;
    DirectX::XMFLOAT4X4 _projection;

    float _aspect = 1.6f;

    float _depthNear = 1.0f;
    float _depthFar = 1700.0f;
    
};


#endif // !CAMERA_H
