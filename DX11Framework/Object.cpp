#include "Object.h"

Object::Object() {
	_color = XMFLOAT4(0.01f, 0.00675f, 0.01f, 1.0f);
	transform = new Transform(this);
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
	UpdatePosition();
	return;
}

void Object::UpdatePosition() {
	// Order: Local transform, to model, to world. --- Future me reading this, this is dumb, ignore this. It should be modelTransform -> parentTransform -> worldTransform.
	transform->UpdateWorldMatrix();
}

