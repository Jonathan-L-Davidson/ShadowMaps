#pragma once

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "Dxgidebug.h"

class ObjectManager;
class ModelManager;
class Renderer;
class Camera;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Update(float deltaTime);

	HRESULT Initialise(Renderer* renderer);

	bool LoadScene(const char* path);

	ObjectManager* GetObjManager() { return _objectManager; };

private:
	ObjectManager* _objectManager;
	ModelManager* _modelManager;
	Renderer* _renderManager;

	Camera* _cam;

	// LightManager
	// CameraHandler;

	void InitHardcodedObjects();

};

#endif // !SCENEMANAGER_H
