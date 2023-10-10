#include "Cube.h"
#include "Renderer.h"

Cube::Cube() {
    return;
}

Cube::~Cube() {
	return;
}

void Cube::Initialise() {

}

void Cube::Update(float deltaTime) {
    XMStoreFloat4x4(&_worldTransform, XMMatrixIdentity() * XMMatrixRotationZ(0.5 * deltaTime) * XMMatrixRotationY(0.5 * deltaTime) * XMLoadFloat4x4(&_worldTransform));
}