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
	float _currentTime = 0.0f;
	float _hoverOffset = 2.0f;
};

#endif