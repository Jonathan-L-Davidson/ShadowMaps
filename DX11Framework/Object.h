#pragma once

#ifndef OBJECT_H

#define OBJECT_H
#include <string>
#include "Transform.h"
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

	// Parent transform - Allows you to assign a parent object where it bases it stems it's origin from.
	void SetParent(Object* parent) { transform->parent = parent->transform; };
	Transform* GetParent() { return transform->parent ? transform->parent : nullptr; };

	void SetPosition(Physics::Vector3 pos) { transform->position = pos; };
	void AddPosition(Physics::Vector3 pos) { transform->position += pos; };
	void SetRotation(Physics::Vector3 rad) { transform->rotation = rad; };
	void GetPosition() { transform->GetPosition(); };
	void GetRotation() { transform->GetRotation(); };
	

	// Manager references.
	void SetManager(ObjectManager* manager) { _objManager = manager; };
	void SetRenderManager(Renderer* manager) { _renderManager = manager; };
	
	// Model related things.
	Model* GetModel() { return _model; };
	void SetModel(Model* model) { _model = model; };
	void SetTexture(Texture* tex) { _model->SetTexture(tex); }

	XMFLOAT4 GetColor() { return _color; };
	void SetColor(XMFLOAT4 color) { _color = color; };

	virtual std::string GetModelName() { return _modelName; };
	void SetModelName(std::string name) { _modelName = name; };
	std::string GetName() { return _name; };
	void SetName(std::string name) { _name = name; };

	virtual void Update(float deltaTime);
	//virtual void UpdateWorldTransform();

	Transform* transform;

protected:
	std::string _name;
	std::string _modelName;

	Model* _model;
	XMFLOAT4 _color;

	virtual void UpdatePosition();
	ObjectManager* _objManager;
	Renderer* _renderManager;

};

#endif