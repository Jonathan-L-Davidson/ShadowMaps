#include "Monkey.h"
#include "Renderer.h"

Monkey::Monkey() {
    return;
}

Monkey::~Monkey() {
    return;
}

void Monkey::Initialise() {
    _color = XMFLOAT4(0.2f, 1.0f, 0.1f, 1.0f);

}

void Monkey::Update(float deltaTime) {
    XMStoreFloat4x4(&_worldTransform, XMMatrixIdentity() * XMMatrixRotationZ(1 * deltaTime) * XMLoadFloat4x4(&_worldTransform) * XMMatrixRotationX(0.5 * deltaTime));
}