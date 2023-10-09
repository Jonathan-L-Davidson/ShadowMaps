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


	void AddObject(Object* obj);
private:
	std::vector<Object*> _objects;

	Renderer* _renderManager;
};

#endif