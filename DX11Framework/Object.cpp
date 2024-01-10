#include "Object.h"
#include "Component.h"

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

template <typename T> T Object::AddComponent(T component, bool awake) {
	
	Component* component = new T();
	if (!AttachComponent(component)) {
		throw new std::exception("Failed to create component!");	
	}

	if (awake) {
		component->Awake();
	}

	return component;
}
bool Object::AttachComponent(Component& component) {
	_components.push_back(&component);
	return true;
}

void Object::DetachComponent(Component& component) {
	for (int i = 0; i = _components.size(); i++) {
		if (&component == _components.at(i)) {
			_components.erase(_components.begin() + i);
		}
	}
}