#include "Camera.h"

Camera::Camera(Transform trans) {
	transform = trans;

	LookFromTrans();
}

Camera::~Camera() {

}

void Camera::UpdateViewMatrix() {
	UpdateProjectionMatrix();
}

void Camera::UpdateProjectionMatrix() {
	XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XMConvertToRadians(90), _aspect, _depthNear, _depthFar));
}

void Camera::SetPosition(XMFLOAT3 pos) {
	transform.SetPosition(pos);
	UpdateViewMatrix();
}

void Camera::SetRotation(XMFLOAT3 rotation) {
	transform.SetRotation(rotation);
	UpdateViewMatrix();
}

void Camera::LookTo(XMFLOAT3 rotation) {
	XMStoreFloat4x4(&_view, XMMatrixLookToLH(XMLoadFloat3(&transform.position), XMLoadFloat3(&rotation), XMLoadFloat3(&_upDir)));
	UpdateViewMatrix();
}

void Camera::LookAt(Transform trans) {
	XMStoreFloat4x4(&_view, XMMatrixLookAtLH(XMLoadFloat3(&transform.position), XMLoadFloat3(&trans.position), XMLoadFloat3(&_upDir)));
	UpdateViewMatrix();
}

//float EulerToView(float x) {
//	float val = ((x * 100) % 90) / 100;
//	return val;
//}

void Camera::LookFromTrans() {

	//XMFLOAT3 rotDir = transform.GetDirection();
	//XMStoreFloat4x4(&_view, XMMatrixLookToLH(XMLoadFloat3(&transform.position), XMLoadFloat3(&rotDir), XMLoadFloat3(&_upDir)));
	XMStoreFloat4x4(&_view, XMMatrixLookToLH(XMLoadFloat3(&transform.position), XMLoadFloat3(&transform.rotation), XMLoadFloat3(&_upDir)));
	UpdateViewMatrix();
}