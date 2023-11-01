#include "Cube.h"
#include "Renderer.h"

Cube::Cube() {
    return;
}

Cube::~Cube() {
	return;
}

void Cube::Initialise() {
    _color = XMFLOAT4(0.05f, 0.05f, 0.05f, 1.0f);
}

void Cube::Update(float deltaTime) {
    Object::Update(deltaTime);
    transform->AddRotation(XMFLOAT3(0.0f, 0.5f * deltaTime, 0.5f * deltaTime));
}