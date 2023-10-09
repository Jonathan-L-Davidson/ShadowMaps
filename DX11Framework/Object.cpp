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

void Object::Update() {
	return;
}
