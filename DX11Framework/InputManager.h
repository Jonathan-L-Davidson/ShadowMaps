#pragma once

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class Renderer;
class SceneManager;

class InputManager
{
public:
	InputManager() {};

	void SetRenderManager(Renderer* renderer) { _renderManager = renderer; };
	void SetSceneManager(SceneManager* sceneManager) { _sceneManager = sceneManager; };

	void Update();

	void HandleRenderKeys();
	void HandleMovementKeys();
	void HandleSceneKeys();
	void HandleMiscKeys();
private:

	Renderer* _renderManager;
	SceneManager* _sceneManager;

	char keyMoveForward = 'W';
	char keyMoveLeft = 'A';
	char keyMoveBackwards = 'S';
	char keyMoveRight = 'D';

	char keyYawCamLeft = 'Q';
	char keyYawCamRight = 'E';
	char keyRollCamLeft = 'Z';
	char keyRollCamRight = 'C';
	char keyPitchCamUp = 'R';
	char keyPitchCaDown = 'F';

	char keyAdjustDepthFarIncrease = ']';
	char keyAdjustDepthFarDecrease = '[';
	char keyAdjustDepthNearIncrease = '#';
	char keyAdjustDepthNearDecrease = '\'';

	bool wireframeToggle = false;
	char keyWireframeToggle = 'X';


};

#endif // !INPUTMANAGER_H

