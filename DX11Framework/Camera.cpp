#include "Camera.h"

Camera::Camera(XMFLOAT3X3 EyeAtUp) {
	Eye = XMFLOAT3(EyeAtUp._11, EyeAtUp._12, EyeAtUp._13);
	At = XMFLOAT3(EyeAtUp._21, EyeAtUp._22, EyeAtUp._23);
	Up = XMFLOAT3(EyeAtUp._31, EyeAtUp._32, EyeAtUp._33);

	XMStoreFloat4x4(&_view, XMMatrixLookAtLH(XMLoadFloat3(&Eye), XMLoadFloat3(&At), XMLoadFloat3(&Up)));
}

Camera::~Camera() {

}

void Camera::UpdateViewMatrix() {
	XMStoreFloat4x4(&_view, XMMatrixLookAtLH(XMLoadFloat3(&Eye), XMLoadFloat3(&At), XMLoadFloat3(&Up)));

}

void Camera::SetPosition(XMFLOAT3 pos) {
	XMStoreFloat3(&Eye, XMLoadFloat3(&pos));
	UpdateViewMatrix();
}

void Camera::SetAt(XMFLOAT3 at) {
	XMStoreFloat3(&At, XMLoadFloat3(&at));
	UpdateViewMatrix();
}

void Camera::SetUp(XMFLOAT3 up) {
	XMStoreFloat3(&Up, XMLoadFloat3(&up));
	UpdateViewMatrix();
}

void Camera::LookAt(XMFLOAT3 pos) {
	XMFLOAT3 localDifference;
	XMStoreFloat3(&localDifference, XMLoadFloat3(&pos) - XMLoadFloat3(&Eye));
	


	XMStoreFloat3(&At, XMLoadFloat3(&localDifference));
	UpdateViewMatrix();
}