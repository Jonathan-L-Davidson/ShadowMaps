#pragma once

#ifndef OBJECT_H

#define OBJECT_H
#include <string>
#include "Transform.h"
#include "model.h"

using namespace DirectX;

class ObjectManager;
class Renderer;
class Component;

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
	Vector3 GetPosition() { return transform->GetPosition(); };
	Vector3 GetRotation() { return transform->GetRotation(); };
	

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

	bool AttachComponent(Component* component);
	void DetachComponent(Component& component);
protected:
	std::string _name;
	std::string _modelName;

	Model* _model;
	XMFLOAT4 _color;

	virtual void UpdatePosition();
	void UpdateComponents(float deltaTime);
	
	ObjectManager* _objManager;
	Renderer* _renderManager;

	std::vector<Component*> _components;

public:
	template <typename T> Component* AddComponent(T type, bool awake = true) {

		T* tempComp = new T();
		Component* component = static_cast<Component*>(tempComp);
		if (!component) {
			throw new std::exception("Incorrect Component type!");
		}
		
		component->Attach(this);

		if (awake) {
			component->Awake();
			component->Start();
		}


		return component;
	}

	template <typename T> inline T* GetComponent() {
		for (int i = 0; i < _components.size(); i++) {
			if (static_cast<T*>(_components.at(i))) {
				return static_cast<T*>(_components.at(i));
			}
		}

		return nullptr;
	}
};

#endif