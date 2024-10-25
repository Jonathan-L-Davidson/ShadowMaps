#include "Transform.h"
#include "Object.h"
#include "model.h"

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

void Transform::UpdateWorldMatrix() {


	XMMATRIX localM = XMMatrixIdentity();
	XMMATRIX parentM = XMMatrixIdentity();

	if (local) {
		localM = local->GetWorldMatrix();
	}
	if (parent) {
		parentM = parent->GetWorldMatrix();
	}

	XMMATRIX rotationMatrix = XMMatrixIdentity();

	//XMFLOAT4 rotationValue = XMFLOAT4(rotation.v.x, rotation.v.y, rotation.v.z, rotation.n);
	XMVECTOR rotationVector = XMLoadFloat4(&rotation);
	rotationMatrix = XMMatrixRotationQuaternion(rotationVector);

	XMMATRIX worldTransform = (XMMatrixIdentity() * XMMatrixScaling(scale.x, scale.y, scale.z) * rotationMatrix) * (XMMatrixIdentity() * XMMatrixTranslation(position.x, position.y, position.z));
	//XMMATRIX worldTransform = (XMMatrixIdentity() * rotationMatrix);

	XMStoreFloat4x4(&_worldTransform, localM * worldTransform * parentM);

}