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

// This is the part where I lose my sanity to stupid complex math. I need to convert an eular angle into a direction.
Physics::Vector3 Transform::GetDirection() {
	Physics::Vector3 dir = Physics::Vector3(
		sinf(rotation.z) * sinf(rotation.y),
		sinf(rotation.z) * sinf(rotation.y),
		sinf(rotation.x)
	);
	return dir;
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