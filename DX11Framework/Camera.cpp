#include "Camera.h"

Camera::Camera(XMFLOAT3X3 EyeAtUp) {
	Eye = XMFLOAT3(EyeAtUp._11, EyeAtUp._12, EyeAtUp._13);
	At = XMFLOAT3(EyeAtUp._21, EyeAtUp._22, EyeAtUp._23);
	Up = XMFLOAT3(EyeAtUp._31, EyeAtUp._32, EyeAtUp._33);

	XMStoreFloat4x4(&_view, XMMatrixLookAtLH(XMLoadFloat3(&Eye), XMLoadFloat3(&At), XMLoadFloat3(&Up)));
}

void Camera::UpdateViewMatrix() {
	XMStoreFloat4x4(&_view, XMMatrixLookAtLH(XMLoadFloat3(&Eye), XMLoadFloat3(&At), XMLoadFloat3(&Up)));

}

void Camera::SetPosition(XMFLOAT3 pos) {
	XMStoreFloat3(&Eye, XMLoadFloat3(&pos));
	UpdateViewMatrix();
}

