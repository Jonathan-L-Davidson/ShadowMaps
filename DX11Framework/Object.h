#pragma once

#ifndef OBJECT_H

#define OBJECT_H
#include <DirectXMath.h>
#include <string>
#include "model.h"

using namespace DirectX;

class ObjectManager;
class Renderer;

class Object
{
public:
	Object();
	~Object();


	virtual void Initialise();

	XMFLOAT4 GetColor() { return _color; };
	void SetColor(XMFLOAT4 color) { _color = color; };

	void SetManager(ObjectManager* manager) { _objManager = manager; };
	void SetRenderManager(Renderer* manager) { _renderManager = manager; };
	void SetPosition(XMFLOAT3 pos);
	XMFLOAT3 GetPosition();
	XMFLOAT4X4 GetTransform() { return _worldTransform; };
	XMMATRIX GetWorldMatrix() { return XMLoadFloat4x4(&_worldTransform); };

	Model* GetModel() { return _model; };
	void SetModel(Model* model) { _model = model; };
	void SetTexture(Texture* tex) { _model->SetTexture(tex); }


	virtual std::string GetModelName() { return GetName(); };
	std::string GetName() { return _name; };
	void SetName(std::string name) { _name = name; };

	virtual void Update(float deltaTime);
protected:
	std::string _name;

	XMFLOAT4X4 _worldTransform;

	Model* _model;
	XMFLOAT4 _color;

	virtual void UpdatePosition();
	ObjectManager* _objManager;
	Renderer* _renderManager;
};

#endif