#pragma once

#ifndef TRANSFOR_H
#define TRANSFOR_H
#include <DirectXMath.h>

#include "Physics/Vector3.h"
#include "Physics/Quaternion.h"

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


	// Rotation helpers!
	void SetRotation(Quaternion rot) { rotation = rot; };
	void SetRotation(Vector3 rot) { rotation = Quaternion(); rotation = MakeQFromEulerAngles(rot.x, rot.y, rot.z); rotation.Normalise(); };
	Quaternion GetRotation() { return rotation; };
	void AddRotation(Quaternion rot) { rotation += rot; };
	void AddRotation(Vector3 rot) { rotation = rotation * MakeQFromEulerAngles(rot.x, rot.y, rot.z); rotation.Normalise(); };


	void UpdateWorldMatrix();

	DirectX::XMFLOAT4X4 GetTransform() { return _worldTransform; };
	DirectX::XMMATRIX GetWorldMatrix() { UpdateWorldMatrix(); return DirectX::XMLoadFloat4x4(&_worldTransform); };

	Transform* parent;
	Transform* local;

	Vector3 position = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 forward = Vector3(0.0f, 0.0f, 1.0f);
	Vector3 right = Vector3();

	Quaternion rotation = Quaternion();
private:
	DirectX::XMFLOAT4X4 _worldTransform;
public:
	Transform operator+(const Transform& add) {
		Transform returnedValue;
		returnedValue.position = position + add.position;

		returnedValue.scale.x = scale.x * add.scale.x;
		returnedValue.scale.y = scale.y * add.scale.y;
		returnedValue.scale.z = scale.z * add.scale.z;

		return returnedValue;
	}

};

#endif