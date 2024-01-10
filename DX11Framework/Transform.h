#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <DirectXMath.h>

#include "Physics/Vector3.h"

using namespace Physics;

class Object;

class Transform
{

public:
	Transform();
	Transform(Object* obj);
	~Transform();

	// Position helpers!
	void SetPosition(Vector3 pos) { position = pos; };
	Vector3 GetPosition() { return position; };
	void AddPosition(Vector3 pos) { position += pos; };

	void SetRotation(Vector3 rad) { rotation = rad; };
	Vector3 GetRotation() { return rotation; };
	void AddRotation(Vector3 rad) { rotation += rad; };
	Vector3 GetDirection();


	void UpdateWorldMatrix();

	DirectX::XMFLOAT4X4 GetTransform() { return _worldTransform; };
	DirectX::XMMATRIX GetWorldMatrix() { return DirectX::XMLoadFloat4x4(&_worldTransform); };

	Transform* parent;
	Transform* local;

	Vector3 position = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
private:
	DirectX::XMFLOAT4X4 _worldTransform;
};

#endif