#include "Pyramid.h"
#include "Renderer.h"

Pyramid::Pyramid() {
    return;
}

Pyramid::~Pyramid() {
    return;
}

void Pyramid::Initialise() {
    _color = XMFLOAT4(0.8f, 0.2f, 0.15f, 1.0f);

}

void Pyramid::Update(float deltaTime) {
    XMStoreFloat4x4(&_worldTransform, XMMatrixIdentity() * XMMatrixRotationY(1 * deltaTime) * XMLoadFloat4x4(&_worldTransform) * XMMatrixRotationY(0.5 * deltaTime));
}