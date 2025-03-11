#include "ObjectManager.h"
#include "Object.h"
#include "ModelManager.h"
#include <stdexcept>

ObjectManager::ObjectManager() {
	return;
}

ObjectManager::~ObjectManager() {
	for (auto obj : _objects) {
		delete obj;
	}
	_objects.clear();
	
	for (auto obj : _bodies) {
		delete obj;
	}
	_bodies.clear();

	_renderManager = nullptr;
	_modelManager = nullptr;

}

Shader* ObjectManager::GetShader(std::string id)
{
	return _modelManager->GetShader(id);
}

void ObjectManager::Update(float deltaTime) {
	for (Object* obj : _objects) {
		if (obj) {
			obj->Update(deltaTime);
		}
	}
}

void ObjectManager::AddObject(Object* obj, Vector3 pos) {
	if(obj->GetName().size() <= 0) { // If the name string is empty, do not add.
		throw std::invalid_argument("Object name is empty!");
		return;
	}
	
	if (obj) {
		_objects.push_back(obj);
		obj->SetManager(this);
		obj->SetRenderManager(_renderManager);
		std::string modelName = obj->GetModelName();
		if (modelName.length() < 1) { modelName = obj->GetName(); }
		Model* model = _modelManager->GetModel(modelName);
		obj->SetModel(model);
		obj->SetPosition(pos); // Fix position stuff lol

		obj->Initialise(); // Todo: Figure out proper OOP practices again.
	}
}

void ObjectManager::AddCollisionBody(Rigidbody* body) { 
	if (body == nullptr) {
		throw new std::exception("Rigidbody is null!");
		return;
	}

	_bodies.push_back(body);
};
