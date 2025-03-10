#pragma once

#ifndef CUBE_H
#define CUBE_H

#include "Object.h"
class Cube : public Object
{
public:
	Cube();
	~Cube();

	void Initialise();
	void Update(float deltaTime);
private:
};

#endif
