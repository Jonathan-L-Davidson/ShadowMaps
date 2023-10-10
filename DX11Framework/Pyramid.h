#pragma once

#ifndef PYRAMID_H
#define PYRAMID_H

#include "Object.h"
class Pyramid : public Object
{
public:
	Pyramid();
	~Pyramid();

	void Initialise();
	void Update(float deltaTime);
private:
};

#endif