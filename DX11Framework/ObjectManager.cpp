#include "ObjectManager.h"
#include "WindowManager.h"

ObjectManager::ObjectManager() {

}

ObjectManager::~ObjectManager() {

}

void ObjectManager::AddObject(Object* obj) {
	if(obj->GetName().size() <= 0) {// If the string is empty, do not add.
		MessageBoxA(WindowManager::GetHandle(), "ERROR: Object has no name!", nullptr, ERROR);
		return;
	}
	
	// If insert returns a value in .second, 
	if (!_objects.insert(std::make_pair(obj->GetName(), obj)).second) {
		std::string obj1 = _objects.at(obj->GetName())->GetName();
		std::string obj2 = obj->GetName();
		MessageBoxA(WindowManager::GetHandle(), std::string("ERROR: Object has two names! " + obj1).c_str(), nullptr, ERROR);
	}

	
}