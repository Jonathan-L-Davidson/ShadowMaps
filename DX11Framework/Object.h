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

	std::string GetName() { return _name; };

	void SetManager(ObjectManager* manager) { _objManager = manager; }
	void SetRenderManager(Renderer* manager) { _renderManager = manager; }
	void SetPosition(XMFLOAT4X4 pos);
	XMFLOAT4X4 GetPosition() { return _pos; };

	Model* GetModel() { return _model; };
	void SetModel(Model* model) { _model = model; };

	void SetName(std::string name) { _name = name; };
protected:
	std::string _name;

	XMFLOAT4X4 _pos;

	virtual void Update();
	Model* _model;


	ObjectManager* _objManager;
	Renderer* _renderManager;
};

#endif