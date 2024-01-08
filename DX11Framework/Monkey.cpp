#include "Monkey.h"
#include "Renderer.h"

Monkey::Monkey() {
    return;
}

Monkey::~Monkey() {
    return;
}

void Monkey::Initialise() {
    _color = XMFLOAT4(0.005f, 0.125f, 0.005f, 1.0f);
    return;
}

void Monkey::Update(float deltaTime) {
    Object::Update(deltaTime);
    
    transform->AddRotation(Vector3(0.5f * deltaTime, 0.0f, 1.0f * deltaTime));
}