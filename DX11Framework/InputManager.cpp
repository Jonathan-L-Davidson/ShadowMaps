#include "InputManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Camera.h"
#include <winuser.h>

#define KeyDown(x) (GetAsyncKeyState(x) & 0x8000)

void InputManager::Update() {

	HandleRenderKeys();
	HandleMovementKeys();
	HandleSceneKeys();
	HandleMiscKeys();
}

void InputManager::HandleRenderKeys() {
	if (KeyDown(keyWireframeToggle)) {
		if (!wireframeToggle) {
			_renderManager->SwapRS('W');
			wireframeToggle = true;
		}
		else {
			_renderManager->SwapRS('D');
			wireframeToggle = false;
		}

	}

}

void InputManager::HandleMovementKeys() {
	Camera* cam = _sceneManager->GetActiveCam();
	
	// WASD.
	{
		if (KeyDown(keyMoveForward)) {
			cam->transform.AddPosition(XMFLOAT3(0, 0, _sceneManager->moveSpeed));
		}
		if (KeyDown(keyMoveLeft)) {
			cam->transform.AddPosition(XMFLOAT3(-_sceneManager->moveSpeed, 0, 0));
		}
		if (KeyDown(keyMoveBackwards)) {
			cam->transform.AddPosition(XMFLOAT3(0, 0, -_sceneManager->moveSpeed));
		}
		if (KeyDown(keyMoveRight)) {
			cam->transform.AddPosition(XMFLOAT3(_sceneManager->moveSpeed, 0, 0));
		}
	}

	// Rotationals. I personally don't like my implementation of it, I really dislike it, even.
	{
		// For dumb me:
		// X - looks left/right
		// Y - looks up/down
		// Z - rolls left/right -- this doesn't, it's some odd value I don't want to learn at the moment.
		if (KeyDown(keyYawCamLeft)) {
			cam->transform.AddRotation(XMFLOAT3(-_sceneManager->rotSpeed, 0, 0));
		}
		if (KeyDown(keyYawCamRight)) {
			cam->transform.AddRotation(XMFLOAT3(_sceneManager->rotSpeed, 0, 0));
		}

		if (KeyDown(keyRollCamLeft)) {
			cam->transform.AddRotation(XMFLOAT3(0, 0, _sceneManager->rotSpeed));
		}
		if (KeyDown(keyRollCamRight)) {
			cam->transform.AddRotation(XMFLOAT3(0, 0, -_sceneManager->rotSpeed));
		}
		
		if (KeyDown(keyPitchCamUp)) {
			cam->transform.AddRotation(XMFLOAT3(0, _sceneManager->rotSpeed, 0));
		}
		if (KeyDown(keyPitchCamDown)) {
			cam->transform.AddRotation(XMFLOAT3(0, -_sceneManager->rotSpeed, 0));
		}

	}
}

void InputManager::HandleSceneKeys() {
}

void InputManager::HandleMiscKeys() {
}

