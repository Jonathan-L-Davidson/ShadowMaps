#include "Pyramid.h"
#include "Renderer.h"

Pyramid::Pyramid() {
    return;
}

Pyramid::~Pyramid() {
    return;
}

void Pyramid::Initialise() {


}

void Pyramid::Update(float deltaTime) {
    XMStoreFloat4x4(&_worldTransform, XMMatrixIdentity() * XMMatrixRotationY(2 * deltaTime) * XMLoadFloat4x4(&_worldTransform) * XMMatrixRotationY(0.5 * deltaTime));
}