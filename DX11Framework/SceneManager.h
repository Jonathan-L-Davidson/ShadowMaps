#pragma once

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "Dxgidebug.h"
#include <vector>

#define CAMERA_AMOUNT		3

#define CA_DEFAULT_WASD	0
#define CA_LOOKAT			1
#define CA_LOOKDOWN		2

class ConstantBuffer;
class SimpleLight;
class ObjectManager;
class ModelManager;
class Renderer;
class Camera;
class Object;
class Transform;

class SceneManager
{
public:
	float moveSpeed = 15.0f;
	const float maxSpeed = 50.0f;
	const float minSpeed = 0.1f;
	float rotSpeed = 1.0f;

	SceneManager();
	~SceneManager();

	void Update(float deltaTime);

	HRESULT Initialise(Renderer* renderer);

	bool LoadScene(const char* path);

	void LoadLights(ConstantBuffer* cbData);

	ObjectManager* GetObjManager() { return _objectManager; };

	void SetActiveCam(Camera* cam) { _activeCam = cam; };
	Camera* GetActiveCam() { return _activeCam; };
	Camera* GetCam(int index) { return _cameras[index]; };
	std::vector<SimpleLight*>* GetShadowLights() { return &_shadowLights; };

	Object* SetActiveObject(int index);
	Object* SetActiveObject(Object* obj, int index);
	Object* GetActiveObject() { return _selectedObj ? _selectedObj : SetActiveObject(_selectedObjIndex); }
	int GetActiveObjectIndex() { return _selectedObjIndex; }
	void UpdateActiveObject();

	unsigned int CycleObjects(int increment);
	
	bool outputTime = false;

private:
	ObjectManager* _objectManager;
	ModelManager* _modelManager;
	Renderer* _renderManager;

	Camera* _activeCam;

	Camera* _cameras[CAMERA_AMOUNT];
	Object* _selectedObj;
	unsigned int _selectedObjIndex;

	std::vector<SimpleLight>* _lights;
	std::vector<SimpleLight*> _shadowLights;

	// CameraHandler;

	void InitHardcodedObjects();
	void SetupCameras();
	void UpdateCameras();
	Object* ParseObjType(const char* type);

};

#endif // !SCENEMANAGER_H
