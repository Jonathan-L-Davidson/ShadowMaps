#pragma once

#ifndef MONKEY_H
#define MONKEY_H
#include "Object.h"

class Monkey : public Object
{
public:
	Monkey();
	~Monkey();

	void Initialise();
	void Update(float deltaTime);

	//std::string GetModelName() { return "Monkey"; };
private:
};

#endif
