#include "ObjectManager.h"
#include <stdexcept>

ObjectManager::ObjectManager() {
	return;
}

ObjectManager::~ObjectManager() {
	for (auto obj : _objects) {
		delete obj;
	}
	_objects.clear();
}

void ObjectManager::Update(float deltaTime) {
	for (Object* obj : _objects) {
		if (obj) {
			obj->Update(deltaTime);
		}
	}
}

void ObjectManager::AddObject(Object* obj) {
	if(obj->GetName().size() <= 0) { // If the name string is empty, do not add.
		throw std::invalid_argument("Object name is empty!");
		return;
	}
	
	if (obj) {
		_objects.push_back(obj);
		obj->SetManager(this);
		obj->SetRenderManager(_renderManager);
		obj->Initialise(); // Todo: Figure out proper OOP practices again.
		obj->SetPosition(XMFLOAT3(2.0f, 3.0f, 15.0f)); // Fix position stuff lol
	}
}