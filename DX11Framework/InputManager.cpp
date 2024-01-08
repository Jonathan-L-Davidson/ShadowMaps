#include "InputManager.h"
#include "DX11Framework.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Camera.h"
#include <winuser.h>

#define KeyDown(x) (GetAsyncKeyState(x) & 0x8000)

using namespace Physics;

void InputManager::Update() {
	if (_renderManager->GetWindowInstance() == GetFocus()) {
		HandleRenderKeys();
		HandleMovementKeys();
		HandleSceneKeys();
		HandleMiscKeys();
	}
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
			cam->transform.AddPosition(Vector3(0, 0, _sceneManager->moveSpeed));
		}
		if (KeyDown(keyMoveLeft)) {
			cam->transform.AddPosition(Vector3(-_sceneManager->moveSpeed, 0, 0));
		}
		if (KeyDown(keyMoveBackwards)) {
			cam->transform.AddPosition(Vector3(0, 0, -_sceneManager->moveSpeed));
		}
		if (KeyDown(keyMoveRight)) {
			cam->transform.AddPosition(Vector3(_sceneManager->moveSpeed, 0, 0));
		}
	}

	// Rotationals. I personally don't like my implementation of it, I really dislike it, even.
	{
		// For dumb me:
		// X - looks left/right
		// Y - looks up/down
		// Z - rolls left/right -- this doesn't, it's some odd value I don't want to learn at the moment.
		if (KeyDown(keyYawCamLeft)) {
			cam->transform.AddRotation(Vector3(-_sceneManager->rotSpeed, 0, 0));
		}
		if (KeyDown(keyYawCamRight)) {
			cam->transform.AddRotation(Vector3(_sceneManager->rotSpeed, 0, 0));
		}

		if (KeyDown(keyRollCamLeft)) {
			cam->transform.AddRotation(Vector3(0, 0, _sceneManager->rotSpeed));
		}
		if (KeyDown(keyRollCamRight)) {
			cam->transform.AddRotation(Vector3(0, 0, -_sceneManager->rotSpeed));
		}
		
		if (KeyDown(keyPitchCamUp)) {
			cam->transform.AddRotation(Vector3(0, _sceneManager->rotSpeed, 0));
		}
		if (KeyDown(keyPitchCamDown)) {
			cam->transform.AddRotation(Vector3(0, -_sceneManager->rotSpeed, 0));
		}

	}
}

void InputManager::HandleSceneKeys() {
	if (KeyDown('1')) {
		_sceneManager->SetActiveCam(_sceneManager->GetCam(CAM_DEFAULT_WASD));
	}
	if (KeyDown('2')) {
		_sceneManager->SetActiveCam(_sceneManager->GetCam(CAM_LOOKAT));
	}
	if (KeyDown('3')) {
		_sceneManager->SetActiveCam(_sceneManager->GetCam(CAM_LOOKDOWN));
	}
}

void InputManager::HandleMiscKeys() {

	if (KeyDown(VK_F5)) {
		_framework->RefreshScene();
	}

	/* // DX11 doesn't like me changing the depth values, woops!
	Camera* cam = _sceneManager->GetActiveCam();

	if (KeyDown(keyAdjustDepthNearIncrease)) {
		cam->SetDepth(cam->GetDepthNear() + 0.01f, 0);
	}
	if (KeyDown(keyAdjustDepthNearDecrease)) {
		cam->SetDepth(cam->GetDepthNear() - 0.01f, 0);
	}
	if (KeyDown(keyAdjustDepthFarIncrease)) {
		cam->SetDepth(0, cam->GetDepthFar() + 0.5f);
	}
	if (KeyDown(keyAdjustDepthFarDecrease)) {
		cam->SetDepth(0, cam->GetDepthFar() - 0.5f);
	}
	*/
}

