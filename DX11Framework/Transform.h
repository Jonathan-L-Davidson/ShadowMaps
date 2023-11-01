#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <DirectXMath.h>

using namespace DirectX;

class Object;

class Transform
{

public:
	Transform();
	Transform(Object* obj);
	~Transform();

	// Position helpers!
	void SetPosition(XMFLOAT3 pos) { position = pos; };
	XMFLOAT3 GetPosition() { return position; };
	void AddPosition(XMFLOAT3 pos);

	void SetRotation(XMFLOAT3 rad) { rotation = rad; };
	XMFLOAT3 GetRotation() { return position; };
	void AddRotation(XMFLOAT3 rad);


	void UpdateWorldMatrix();

	XMFLOAT4X4 GetTransform() { return _worldTransform; };
	XMMATRIX GetWorldMatrix() { return XMLoadFloat4x4(&_worldTransform); };

	Transform* parent;
	Transform* local;

	XMFLOAT3 position;
	XMFLOAT3 rotation;
private:
	XMFLOAT4X4 _worldTransform;
};

#endif