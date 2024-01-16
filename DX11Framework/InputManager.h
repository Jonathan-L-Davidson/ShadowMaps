#pragma once

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <winuser.h>

class Renderer;
class SceneManager;
class DX11Framework;

class InputManager
{
public:
	InputManager() {};

	void SetRenderManager(Renderer* renderer) { _renderManager = renderer; };
	void SetSceneManager(SceneManager* sceneManager) { _sceneManager = sceneManager; };
	void SetFramework(DX11Framework* framework) { _framework = framework; };

	void Update();

	void HandleRenderKeys();
	void HandleMovementKeys();
	void HandleSceneKeys();
	void HandleMiscKeys();
private:

	bool _keyDown[255];

	Renderer* _renderManager;
	SceneManager* _sceneManager;
	DX11Framework* _framework;

	char keyMoveForward = 'W';
	char keyMoveLeft = 'A';
	char keyMoveBackwards = 'S';
	char keyMoveRight = 'D';

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
	char keyPhysMoveForward = VK_UP;
	char keyPhysMoveBackwards = VK_DOWN;
	char keyPhysMoveLeft = VK_LEFT;
	char keyPhysMoveRight = VK_RIGHT;

	char keyCycleObjUp = VK_PRIOR; // page up
	char keyCycleObjDown = VK_NEXT; // page down
	char keyOutputDelta = VK_END;


	bool HandleKeyDown(const char input);
	bool HandleKeyUp(const char input);
	bool HandleKeyPressed(const char input);
	void OutputCurrentObject();
};

#endif // !INPUTMANAGER_H

