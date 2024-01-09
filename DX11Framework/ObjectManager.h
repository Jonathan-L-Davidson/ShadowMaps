#pragma once

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include <string>
#include <vector>
#include "Object.h"

class Renderer;
class ModelManager;

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void SetRenderManager(Renderer* manager) { _renderManager = manager; };
	void SetModelManager(ModelManager* manager) { _modelManager = manager; };

	std::vector<Object*> GetObjects() { return _objects; };

	void Update(float deltaTime);

	void AddObject(Object* obj, XMFLOAT3 pos);
private:
	std::vector<Object*> _objects;

	Renderer* _renderManager;
	ModelManager* _modelManager;
};

#endif