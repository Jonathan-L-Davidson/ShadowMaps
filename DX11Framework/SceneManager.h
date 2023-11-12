#pragma once

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "Dxgidebug.h"

#define CAMERA_AMOUNT		3

#define CAM_DEFAULT_WASD	0
#define CAM_LOOKAT			1
#define CAM_LOOKDOWN		2

class ObjectManager;
class ModelManager;
class Renderer;
class Camera;
class Object;
class Transform;

class SceneManager
{
public:
	float moveSpeed = 1.2;
	float rotSpeed = 1.0f;

	SceneManager();
	~SceneManager();

	void Update(float deltaTime);

	HRESULT Initialise(Renderer* renderer);

	bool LoadScene(const char* path);

	ObjectManager* GetObjManager() { return _objectManager; };

	void SetActiveCam(Camera* cam) { _activeCam = cam; };
	Camera* GetActiveCam() { return _activeCam; };
	Camera* GetCam(int index) { return _cameras[index]; };

private:
	ObjectManager* _objectManager;
	ModelManager* _modelManager;
	Renderer* _renderManager;

	Camera* _activeCam;

	Camera* _cameras[CAMERA_AMOUNT];
	Transform* _selectedObj;

	// LightManager
	// CameraHandler;

	void InitHardcodedObjects();
	void SetupCameras();
	void UpdateCameras();
	Object* ParseObjType(const char* type);

};

#endif // !SCENEMANAGER_H
