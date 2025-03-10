#pragma once

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <winuser.h>

#include <Mouse.h>

class Renderer;
class SceneManager;
class DX11Framework;
class Camera;

class InputManager
{
public:
	InputManager() {};

	void SetRenderManager(Renderer* renderer) { _renderManager = renderer; };
	void SetSceneManager(SceneManager* sceneManager) { _sceneManager = sceneManager; };
	void SetFramework(DX11Framework* framework) { _framework = framework; };
	void SetFlyCam(bool val);

	void Initialise();
	void Update(float deltaTime);

	void HandleRenderKeys();
	void HandleMovementKeys(float deltaTime);
	void HandleSceneKeys();
	void HandleMiscKeys();
	void HandleMouse(float deltaTime);
private:

	bool _keyDown[255];

	Renderer* _renderManager;
	SceneManager* _sceneManager;
	DX11Framework* _framework;
	Camera* _cam;

	DirectX::Mouse* _mouse;
	DirectX::Mouse::ButtonStateTracker _mouseButtons;
	char keyToggleFlyCam = 'F';

	char keyMoveForward = 'W';
	char keyMoveLeft = 'A';
	char keyMoveBackwards = 'S';
	char keyMoveRight = 'D';
	char keyMoveUp = VK_SPACE;
	char keyMoveDown = VK_CONTROL;

	char keyYawCamLeft = 'Q';
	char keyYawCamRight = 'E';
	char keyRollCamLeft = 'Z';
	char keyRollCamRight = 'C';
	char keyPitchCamUp = 'R';
	char keyPitchCamDown = 'F';

	char keyAdjustDepthFarIncrease = 'I';
	char keyAdjustDepthFarDecrease = 'O';
	char keyAdjustDepthNearIncrease = 'K';
	char keyAdjustDepthNearDecrease = 'L';

	bool wireframeToggle = false;
	char keyWireframeToggle = 'X';


	float moveSpeed = 5.0f;
	float rotationalSpeed = 50.0f;
	float jumpForce = 100.0f;
	char keyPhysMoveForward = VK_UP;
	char keyPhysMoveBackwards = VK_DOWN;
	char keyPhysMoveLeft = VK_LEFT;
	char keyPhysMoveRight = VK_RIGHT;
	char keyPhysRotation = VK_SHIFT; // When holding down shift up, down, left & right will apply rotational forces instead.
	char keyPhysJump = VK_SPACE;
	char keyPhysConstantVelToggle = VK_HOME;
	char keyPhysConstantAccToggle = VK_INSERT;

	char keyCycleObjUp = VK_PRIOR; // page up
	char keyCycleObjDown = VK_NEXT; // page down
	char keyOutputDelta = VK_END;


	bool HandleKeyDown(const char input);
	bool HandleKeyUp(const char input);
	bool HandleKeyPressed(const char input);
	void OutputCurrentObject();
};

#endif // !INPUTMANAGER_H

