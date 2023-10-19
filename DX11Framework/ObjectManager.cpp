#include "ObjectManager.h"
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

	_renderManager = nullptr;
	_modelManager = nullptr;

}

void ObjectManager::Update(float deltaTime) {
	for (Object* obj : _objects) {
		if (obj) {
			obj->Update(deltaTime);
		}
	}
}

void ObjectManager::AddObject(Object* obj, XMFLOAT3 pos) {
	if(obj->GetName().size() <= 0) { // If the name string is empty, do not add.
		throw std::invalid_argument("Object name is empty!");
		return;
	}
	
	if (obj) {
		_objects.push_back(obj);
		obj->SetManager(this);
		obj->SetRenderManager(_renderManager);
		Model* model = _modelManager->GetModel(obj->GetModelName());
		obj->SetModel(model);
		obj->SetPosition(pos); // Fix position stuff lol

		obj->Initialise(); // Todo: Figure out proper OOP practices again.
	}
}