#pragma once

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include <string>
#include <vector>
#include "Object.h"

class Renderer;
class ModelManager;
class Rigidbody;

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void SetRenderManager(Renderer* manager) { _renderManager = manager; };
	void SetModelManager(ModelManager* manager) { _modelManager = manager; };
	Shader* GetShader(std::string id);

	std::vector<Object*> GetObjects() { return _objects; };
	const std::vector<Rigidbody*>& GetBodies() { return _bodies; };

	void Update(float deltaTime);

	void AddObject(Object* obj, Vector3 pos);
	void AddCollisionBody(Rigidbody* body);
private:
	std::vector<Object*> _objects;
	std::vector<Rigidbody*> _bodies;

	Renderer* _renderManager;
	ModelManager* _modelManager;
};

#endif