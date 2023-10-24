#include "Object.h"

Object::Object() {
	_color = XMFLOAT4(0.01f, 0.00675f, 0.01f, 1.0f);
	Initialise();
}

Object::~Object() {
	_model = nullptr;
	_objManager = nullptr;
	_renderManager = nullptr;
}

void Object::Initialise() {
	return;
}

void Object::Update(float deltaTime) {
	return;
}

void Object::UpdatePosition() {
	// Order: Local transform, to model, to world.

	XMFLOAT4X4 localTransform = _model->GetTransform();
	XMStoreFloat4x4(&_worldTransform, XMMatrixIdentity() * XMLoadFloat4x4(&localTransform) * XMLoadFloat4x4(&_worldTransform));

}

// SETTERS & GETTERS
void Object::SetPosition(XMFLOAT3 pos) {
	XMStoreFloat4x4(&_worldTransform, XMMatrixIdentity() * XMMatrixTranslation(pos.x, pos.y, pos.z));
}

XMFLOAT3 Object::GetPosition() {
	return XMFLOAT3(_worldTransform._11, _worldTransform._22, _worldTransform._33);
}