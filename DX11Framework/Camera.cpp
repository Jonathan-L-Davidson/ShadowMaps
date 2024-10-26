#include "Camera.h"

using namespace DirectX;


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
	DirectX::XMStoreFloat4x4(&_projection, DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(90), _aspect, _depthNear, _depthFar));
}

void Camera::SetPosition(Vector3 pos) {
	transform.SetPosition(pos);
	UpdateViewMatrix();
}

void Camera::LookTo(Quaternion rotation) {
	DirectX::XMFLOAT3 position = DirectX::XMFLOAT3(transform.position.x, transform.position.y, transform.position.z);
	//Vector3 rotationEuler = MakeEulerAnglesFromQ(rotation);
	Vector3 rotationEuler = rotation.ToEuler();
	DirectX::XMFLOAT3 rot = DirectX::XMFLOAT3(rotationEuler.x, rotationEuler.y, rotationEuler.z);
	DirectX::XMFLOAT3 upDir = DirectX::XMFLOAT3(_upDir.x, _upDir.y, _upDir.z);
	
	DirectX::XMStoreFloat4x4(&_view, DirectX::XMMatrixLookToLH(DirectX::XMLoadFloat3(&position), DirectX::XMLoadFloat3(&rot), DirectX::XMLoadFloat3(&upDir)));
	UpdateViewMatrix();
}

void Camera::LookAt(Transform trans) {
	DirectX::XMFLOAT3 position = DirectX::XMFLOAT3(transform.position.x, transform.position.y, transform.position.z);
	DirectX::XMFLOAT3 transPosition = DirectX::XMFLOAT3(trans.position.x, trans.position.y, trans.position.z);
	DirectX::XMFLOAT3 upDir = DirectX::XMFLOAT3(_upDir.x, _upDir.y, _upDir.z);

	DirectX::XMStoreFloat4x4(&_view, DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&position), DirectX::XMLoadFloat3(&transPosition), DirectX::XMLoadFloat3(&upDir)));
	UpdateViewMatrix();
}

//float EulerToView(float x) {
//	float val = ((x * 100) % 90) / 100;
//	return val;
//}

void Camera::LookFromTrans() {

	//Vector3 rotDir = transform.GetDirection();
	//XMStoreFloat4x4(&_view, XMMatrixLookToLH(XMLoadFloat3(&transform.position), XMLoadFloat3(&rotDir), XMLoadFloat3(&_upDir)));
	DirectX::XMStoreFloat4x4(&_view, DirectX::XMMatrixLookToLH(transform.position, transform.rotation, _upDir));
	UpdateViewMatrix();
}

void Camera::LookFlyCam()
{
	DirectX::XMFLOAT3 position = DirectX::XMFLOAT3(transform.position.x, transform.position.y, transform.position.z);
	DirectX::XMFLOAT3 transPosition = transform.position + lookAtTrans.position;
	DirectX::XMFLOAT3 upDir = DirectX::XMFLOAT3(_upDir.x, _upDir.y, _upDir.z);

	DirectX::XMStoreFloat4x4(&_view, DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&position), DirectX::XMLoadFloat3(&transPosition), DirectX::XMLoadFloat3(&upDir)));
	UpdateViewMatrix();
}

//void Camera::LookFromTrans() {
//	DirectX::XMFLOAT3 position = DirectX::XMFLOAT3(transform.position.x, transform.position.y, transform.position.z);
//	Vector3 rotationEuler = MakeEulerAnglesFromQ(transform.rotation);
//	DirectX::XMFLOAT3 rotation = DirectX::XMFLOAT3(rotationEuler.x, rotationEuler.y, rotationEuler.z);
//	DirectX::XMFLOAT3 upDir = DirectX::XMFLOAT3(_upDir.x, _upDir.y, _upDir.z);
//
//	//Vector3 rotDir = transform.GetDirection();
//	//XMStoreFloat4x4(&_view, XMMatrixLookToLH(XMLoadFloat3(&transform.position), XMLoadFloat3(&rotDir), XMLoadFloat3(&_upDir)));
//	DirectX::XMStoreFloat4x4(&_view, DirectX::XMMatrixLookToLH(DirectX::XMLoadFloat3(&position), DirectX::XMLoadFloat3(&rotation), DirectX::XMLoadFloat3(&upDir)));
//	UpdateViewMatrix();
//}