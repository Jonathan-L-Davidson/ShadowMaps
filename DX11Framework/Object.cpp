#include "Object.h"

Object::Object() {
	Initialise();
}

Object::~Object() {
	delete _model; // TODO: Model manager checking object references.
	_objManager = nullptr;
}

void Object::Initialise() {
	return;
}

void Object::Update(float deltaTime) {
	return;
}


// SETTERS & GETTERS
void Object::SetPosition(XMFLOAT3 pos) {
	XMStoreFloat4x4(&_worldPos, XMMatrixIdentity() * XMMatrixTranslation(pos.x, pos.y, pos.z));
}