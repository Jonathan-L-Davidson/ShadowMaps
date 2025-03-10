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
    Object::Update(deltaTime);

    // Hovering effect.
    SetPosition(Vector3(transform->position.x, (transform->position.y + sin(_currentTime * _hoverOffset) * deltaTime), transform->position.z));

    _currentTime += deltaTime;
}