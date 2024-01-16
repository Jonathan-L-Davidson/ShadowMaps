#include "Object.h"
#include "Component.h"

Object::Object() {
	_color = XMFLOAT4(0.01f, 0.00675f, 0.01f, 1.0f);
	transform = new Transform(this);
}

Object::~Object() {
	_model = nullptr;
	_objManager = nullptr;
	_renderManager = nullptr;
}

void Object::Initialise() {
	for (Component* component : _components) {
		component->Start();
	}
	return;
}

void Object::Update(float deltaTime) {
	UpdatePosition();
	UpdateComponents(deltaTime);
	return;
}

void Object::UpdatePosition() {
	// Order: Local transform, to model, to world. --- Future me reading this, this is dumb, ignore this. It should be modelTransform -> parentTransform -> worldTransform.
	transform->UpdateWorldMatrix();
}

void Object::UpdateComponents(float deltaTime) {
	for (Component* comp : _components) {
		if (comp != nullptr)	comp->Update(deltaTime);
	}
}

bool Object::AttachComponent(Component* component) {
	_components.push_back(component);
	return true;
}

void Object::DetachComponent(Component& component) {
	for (int i = 0; i = _components.size(); i++) {
		if (&component == _components.at(i)) {
			_components.erase(_components.begin() + i);
		}
	}
}