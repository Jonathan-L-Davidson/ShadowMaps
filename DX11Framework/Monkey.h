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
private:
};

#endif
