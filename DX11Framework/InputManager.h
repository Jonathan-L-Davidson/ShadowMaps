#pragma once

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

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


};

#endif // !INPUTMANAGER_H

