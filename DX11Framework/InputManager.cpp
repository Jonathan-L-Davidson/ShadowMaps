#include "Debug.h"
#include "InputManager.h"
#include "DX11Framework.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "PhysicsComponent.h"
#include "Object.h"

#define KeyDown(x) ((GetAsyncKeyState(x) & 0x8000))

using namespace Physics;

bool InputManager::HandleKeyDown(const char input) {

	bool state = KeyDown(input);

	_keyDown[input] = state;

	return state;
}

bool InputManager::HandleKeyUp(const char input) {
	bool prevFrameInput = _keyDown[input];
	bool state = HandleKeyDown(input);
	if (!state && prevFrameInput) { // if we are not pressing the button, and the keydown in the previous frame was true.
		return true;
	}
	return false;
}

bool InputManager::HandleKeyPressed(const char input) {
	bool prevFrameInput = _keyDown[input];
	bool state = HandleKeyDown(input);
	if (!prevFrameInput && state) { // The inverse of HandleKeyUp
		return true;
	}
	return false;
}


void InputManager::OutputCurrentObject() {
	int index = _sceneManager->GetActiveObjectIndex();
	Object* currentObj = _sceneManager->GetActiveObject();
	DebugPrintF("\nINPUT MANAGER: Selected Object is now: %i | %s\n", index, currentObj->GetName().c_str());

}

void InputManager::Update(float deltaTime) {
	if (_renderManager->GetWindowInstance() == GetFocus()) {
		HandleRenderKeys();
		HandleMovementKeys(deltaTime);
		HandleSceneKeys();
		HandleMiscKeys();
	}
}

void InputManager::HandleRenderKeys() {
	if (HandleKeyUp(keyWireframeToggle)) {
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

void InputManager::HandleMovementKeys(float deltaTime) {
	Camera* cam = _sceneManager->GetActiveCam();
	
	PhysicsComponent* physicsObj = _sceneManager->GetActiveObject()->GetComponent<PhysicsComponent>();

	// WASD.
	{
		if (HandleKeyDown(keyMoveForward)) {
			cam->transform.AddPosition(Vector3(0, 0, _sceneManager->moveSpeed));
		}
		if (HandleKeyDown(keyMoveLeft)) {
			cam->transform.AddPosition(Vector3(-_sceneManager->moveSpeed, 0, 0));
		}
		if (HandleKeyDown(keyMoveBackwards)) {
			cam->transform.AddPosition(Vector3(0, 0, -_sceneManager->moveSpeed));
		}
		if (HandleKeyDown(keyMoveRight)) {
			cam->transform.AddPosition(Vector3(_sceneManager->moveSpeed, 0, 0));
		}
	}
	
	if (physicsObj != nullptr) {
		if (HandleKeyPressed(keyPhysConstantVelToggle)) {
			physicsObj->useConstantVelocity = !physicsObj->useConstantVelocity;
			DebugPrintF("Object's use constant velocity: %s\n", physicsObj->useConstantVelocity ? "True" : "False");
		}

		if (HandleKeyPressed(keyPhysConstantAccToggle)) {
			physicsObj->useConstantAcceleration = !physicsObj->useConstantAcceleration;
			DebugPrintF("Object's use constant acceleration: %s\n", physicsObj->useConstantAcceleration ? "True" : "False");
		}

		if (HandleKeyDown(keyPhysMoveForward)) {
			if (HandleKeyDown(keyPhysRotation)) { // Use rotation instead when shift is held.
				physicsObj->AddRotationalForce(Vector3(0, rotationalSpeed, 0));
			}
			else {
				physicsObj->AddForce(Vector3(0, 0, moveSpeed));
			}
		}
		if (HandleKeyDown(keyPhysMoveBackwards)) {
			if (HandleKeyDown(keyPhysRotation)) { // Use rotation instead when shift is held.
				physicsObj->AddRotationalForce(Vector3(0, -rotationalSpeed, 0));
			}
			else {
				physicsObj->AddForce(Vector3(0, 0, -moveSpeed));
			}
		}
		if (HandleKeyDown(keyPhysMoveLeft)) {
			if (HandleKeyDown(keyPhysRotation)) { // Use rotation instead when shift is held.
				physicsObj->AddRotationalForce(Vector3(rotationalSpeed, 0, 0));
			}
			else {
				physicsObj->AddForce(Vector3(-moveSpeed, 0, 0));
			}
		}
		if (HandleKeyDown(keyPhysMoveRight)) {
			if (HandleKeyDown(keyPhysRotation)) { // Use rotation instead when shift is held.
				physicsObj->AddRotationalForce(Vector3(-rotationalSpeed, 0, 0));
			}
			else {
				physicsObj->AddForce(Vector3(moveSpeed, 0, 0));
			}
		}
		if (HandleKeyDown(keyPhysJump)) {
			physicsObj->AddForce(Vector3(0, jumpForce, 0));
		}

		if (HandleKeyDown('H')) {
			_sceneManager->GetActiveObject()->transform->rotation.AddScaledVector(Vector3(0,1,0), deltaTime);
		}
		if (HandleKeyDown('J')) {
			_sceneManager->GetActiveObject()->transform->rotation.AddScaledVector(Vector3(0, -1, 0), deltaTime);
		}

	}
	

	// Rotationals. I personally don't like my implementation of it, I really dislike it, even.
	{
		// For dumb me:
		// X - looks left/right
		// Y - looks up/down
		// Z - rolls left/right -- this doesn't, it's some odd value I don't want to learn at the moment.
		//if (HandleKeyDown(keyYawCamLeft)) {
		//	cam->transform.AddRotation(Vector3(-_sceneManager->rotSpeed, 0, 0));
		//}
		//if (HandleKeyDown(keyYawCamRight)) {
		//	cam->transform.AddRotation(Vector3(_sceneManager->rotSpeed, 0, 0));
		//}

		//if (HandleKeyDown(keyRollCamLeft)) {
		//	cam->transform.AddRotation(Vector3(0, 0, _sceneManager->rotSpeed));
		//}
		//if (HandleKeyDown(keyRollCamRight)) {
		//	cam->transform.AddRotation(Vector3(0, 0, -_sceneManager->rotSpeed));
		//}
		//
		//if (HandleKeyDown(keyPitchCamUp)) {
		//	cam->transform.AddRotation(Vector3(0, _sceneManager->rotSpeed, 0));
		//}
		//if (HandleKeyDown(keyPitchCamDown)) {
		//	cam->transform.AddRotation(Vector3(0, -_sceneManager->rotSpeed, 0));
		//}

	}
}

void InputManager::HandleSceneKeys() {
	if (HandleKeyPressed('1')) {
		_sceneManager->SetActiveCam(_sceneManager->GetCam(CAM_DEFAULT_WASD));
	}
	if (HandleKeyPressed('2')) {
		_sceneManager->SetActiveCam(_sceneManager->GetCam(CAM_LOOKAT));
	}
	if (HandleKeyPressed('3')) {
		_sceneManager->SetActiveCam(_sceneManager->GetCam(CAM_LOOKDOWN));
	}

	if (HandleKeyPressed(keyCycleObjUp)) {
		_sceneManager->CycleObjects(1);
		OutputCurrentObject();
	}

	if (HandleKeyPressed(keyCycleObjDown)) {
		_sceneManager->CycleObjects(-1);
		OutputCurrentObject();
	}
}

void InputManager::HandleMiscKeys() {

	if (HandleKeyPressed(VK_F5)) {
		_framework->RefreshScene();
	}

	if (HandleKeyPressed(keyOutputDelta)) {
		_sceneManager->outputTime = !_sceneManager->outputTime;
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

