#pragma once

#if !defined(OBJECTMANAGER_H)
#define OBJECTMANAGER_H

#include "Object.h"
#include <string>
#include <map>

class ObjectManager
{
public:
	ObjectManager() {};
	~ObjectManager() {};

	std::vector<Object> GetObjects() { return _objects; };

	static void AddObject(Object* obj);
private:
	std::map<std::string, Object*> _objects;
};

#endif