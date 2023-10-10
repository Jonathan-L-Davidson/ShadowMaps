#pragma once

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Object.h"
#include <string>
#include <vector>

class Renderer;

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void SetRenderManager(Renderer* manager) { _renderManager = manager; };

	std::vector<Object*> GetObjects() { return _objects; };

	void Update(float deltaTime);

	void AddObject(Object* obj, XMFLOAT3 pos);
private:
	std::vector<Object*> _objects;

	Renderer* _renderManager;
};

#endif