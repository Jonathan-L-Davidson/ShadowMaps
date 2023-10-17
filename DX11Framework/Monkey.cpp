#include "Monkey.h"
#include "Renderer.h"

Monkey::Monkey() {
    return;
}

Monkey::~Monkey() {
    return;
}

void Monkey::Initialise() {
    _color = XMFLOAT4(0.05f, 0.125f, 0.05f, 1.0f);
    return;
}

void Monkey::Update(float deltaTime) {
    XMStoreFloat4x4(&_worldTransform, XMMatrixIdentity() * XMMatrixRotationZ(1 * deltaTime) * XMLoadFloat4x4(&_worldTransform) * XMMatrixRotationX(0.5 * deltaTime));
}