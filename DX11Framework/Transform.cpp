#include "Transform.h"
#include "Object.h"
#include "model.h"

// This shouldnt be here, but it makes my life easier so screw it.
XMFLOAT3 ADD(XMFLOAT3 a, XMFLOAT3 b) {
	return XMFLOAT3(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	);
}

Transform::Transform() {

}

Transform::Transform(Object* obj) {
	Model* objModel = obj->GetModel();
	if (objModel) {
		local = objModel->transform;
	}

}

Transform::~Transform() {
	parent = nullptr;
	local = nullptr;
}

void Transform::AddPosition(XMFLOAT3 pos) {
	position = ADD(position, pos);
}

void Transform::AddRotation(XMFLOAT3 rad) {
	rotation = ADD(rotation, rad);
}

void Transform::UpdateWorldMatrix() {


	XMMATRIX localM = XMMatrixIdentity();
	XMMATRIX parentM = XMMatrixIdentity();

	if (local) {
		localM = local->GetWorldMatrix();
	}
	if (parent) {
		parentM = parent->GetWorldMatrix();
	}

	XMMATRIX worldTransform = (XMMatrixIdentity() * XMMatrixScaling(scale.x, scale.y, scale.z) * XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z)) * (XMMatrixIdentity() * XMMatrixTranslation(position.x, position.y, position.z));

	XMStoreFloat4x4(&_worldTransform, localM * worldTransform * parentM);

}