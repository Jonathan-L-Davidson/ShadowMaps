#include "Component.h"
#include "Object.h"
#include <exception>

Component::Component() {
	
}

Component::~Component() {
	Destroy();
}

void Component::Awake(Object* owner) {
	if (!owner) {
		throw new std::exception("No object attached!");
	}
	_owner = owner;
}

void Component::Start() {
	return;
}

void Component::Update(float deltaTime) {
	return;
}

void Component::Destroy() {
	Detach(_owner);
	_owner = nullptr;
}

void Component::Attach(Object* obj) {
	if (_owner) {
		Detach(_owner);
	}

	if (obj->AttachComponent(this)) {
		_owner = obj;
	}
	else {
		throw new std::exception("Object failed to be attached!");
	}
}

void Component::Detach(Object* obj) {
	if (obj) {
		obj->DetachComponent(*this);
		_owner = nullptr;
	}
}
