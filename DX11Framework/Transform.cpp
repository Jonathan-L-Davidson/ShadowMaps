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

	XMMATRIX rotationMatrix;
	
	CalculateTransformMatrixRowMajor(rotationMatrix, Vector3(0,0,0), rotation);

	XMMATRIX worldTransform = (XMMatrixIdentity() * XMMatrixScaling(scale.x, scale.y, scale.z) * rotationMatrix) * (XMMatrixIdentity() * XMMatrixTranslation(position.x, position.y, position.z));

	XMStoreFloat4x4(&_worldTransform, localM * worldTransform * parentM);

}