#pragma once

#if !defined(OBJECT_H)
#define OBJECT_H
#include <DirectXMath.h>
#include <string>
#include "model.h"

using namespace DirectX;

class Object
{
public:
	Object();
	~Object();


	virtual void Initialise();

	std::string GetName() { return _name; };

	void SetPosition(XMFLOAT4X4 pos);
	XMFLOAT4X4 GetPosition() { return _pos; };

	Model* GetModel() { return _model; };
	void SetModel(Model* model) { _model = model; };
private:
	std::string _name;

	XMFLOAT4X4 _pos;

	virtual void Update();
	Model* _model;

};

#endif