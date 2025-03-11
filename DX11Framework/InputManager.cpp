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

#ifdef USE_DIRECTXTK_MATH
using namespace DirectX;
#else
using namespace Physics;
#endif

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

void InputManager::SetFlyCam(bool val)
{
	_cam->flyCam = val;
	_mouse->SetMode((DirectX::Mouse::Mode)val);
}

void InputManager::Initialise()
{
	_mouse = new DirectX::Mouse();
	_mouse->SetWindow(_renderManager->GetWindowInstance());
	_mouse->SetMode(DirectX::Mouse::MODE_ABSOLUTE);
}

void InputManager::Update(float deltaTime) {
	_cam = _sceneManager->GetActiveCam();

	if (_renderManager->GetWindowInstance() == GetFocus()) {
		HandleRenderKeys();
		HandleMovementKeys(deltaTime);
		HandleSceneKeys();
		HandleMiscKeys();
		HandleMouse(deltaTime);
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
	
	//PhysicsComponent* physicsObj = _sceneManager->GetActiveObject()->GetComponent<PhysicsComponent>();

	// WASD.
	{
		if (HandleKeyDown(keyMoveForward)) {
			if (_cam->flyCam) {
				_cam->transform.AddPosition(_cam->lookAtTrans.position * (float)(deltaTime * _sceneManager->moveSpeed));
			}
			else {
				_cam->transform.AddPosition(Vector3(0, 0, _sceneManager->moveSpeed) * deltaTime);
			}
		}
		if (HandleKeyDown(keyMoveLeft)) {
			if (_cam->flyCam) {
				_cam->transform.AddPosition(_cam->transform.right * (float)(deltaTime * _sceneManager->moveSpeed));
			}
			else {
				_cam->transform.AddPosition(Vector3(-_sceneManager->moveSpeed, 0, 0) * deltaTime);
			}
		}
		if (HandleKeyDown(keyMoveBackwards)) {
			if (_cam->flyCam) {
				_cam->transform.AddPosition(_cam->lookAtTrans.position * (float)(deltaTime * -_sceneManager->moveSpeed));
			}
			else {
				_cam->transform.AddPosition(Vector3(0, 0, -_sceneManager->moveSpeed) * deltaTime);
			}
		}
		if (HandleKeyDown(keyMoveRight)) {
			if (_cam->flyCam) {
				_cam->transform.AddPosition(_cam->transform.right * (float)(deltaTime * -_sceneManager->moveSpeed));
			}
			else {
				_cam->transform.AddPosition(Vector3(_sceneManager->moveSpeed, 0, 0) * deltaTime);
			}
		}
	}
	
	// Physics (Unused for shadow project)
	/*
	{
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
				_sceneManager->GetActiveObject()->transform->AddRotation(Vector3(0, 1, 0));
			}
			if (HandleKeyDown('J')) {
				_sceneManager->GetActiveObject()->transform->AddRotation(Vector3(0, -1, 0));
			}
		}
	}
	*/

	// Misc additionals (Raise cam & lower cam)
	{
		if (HandleKeyDown(keyMoveUp)) {
			_cam->transform.AddPosition(_cam->transform.up* (float)(deltaTime * _sceneManager->moveSpeed));
		}
		if (HandleKeyDown(keyMoveDown)) {
			_cam->transform.AddPosition(_cam->transform.up* (float)(deltaTime * -_sceneManager->moveSpeed));
		}

		// DX11 doesn't like me changing the depth values, woops!
		if (KeyDown(keyAdjustDepthNearIncrease)) {
			_cam->SetDepth(_cam->GetDepthNear() + 0.001f * deltaTime, _cam->GetDepthFar());
		}
		if (KeyDown(keyAdjustDepthNearDecrease)) {
			_cam->SetDepth(_cam->GetDepthNear() - 0.001f * deltaTime, _cam->GetDepthFar());
		}
		if (KeyDown(keyAdjustDepthFarIncrease)) {
			_cam->SetDepth(_cam->GetDepthNear(), _cam->GetDepthFar() + 100.0f * deltaTime);
		}
		if (KeyDown(keyAdjustDepthFarDecrease)) {
			_cam->SetDepth(_cam->GetDepthNear(), _cam->GetDepthFar() - 100.0f * deltaTime);
		}
	}
}

void InputManager::HandleSceneKeys() {
	if (HandleKeyPressed('1')) {
		_sceneManager->SetActiveCam(_sceneManager->GetCam(CA_DEFAULT_WASD));
	}
	if (HandleKeyPressed('2')) {
		_sceneManager->SetActiveCam(_sceneManager->GetCam(CA_LOOKAT));
	}
	if (HandleKeyPressed('3')) {
		_sceneManager->SetActiveCam(_sceneManager->GetCam(CA_LOOKDOWN));
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
}


#define VIEW_PITCH_CLAMP	M_PI_2 + 0.01f

void InputManager::HandleMouse(float deltaTime)
{
	auto mouse = _mouse->GetState();
	_mouseButtons.Update(mouse);

	_sceneManager->moveSpeed += mouse.scrollWheelValue * deltaTime;
	_mouse->ResetScrollWheelValue();
	
	_sceneManager->moveSpeed = min(_sceneManager->maxSpeed, _sceneManager->moveSpeed);
	_sceneManager->moveSpeed = max(_sceneManager->minSpeed, _sceneManager->moveSpeed);

	//DebugPrintF("Move Speed: %f\n", _sceneManager->moveSpeed);

	if(_cam->flyCam) {
		//DebugPrintF("Mouse pos X: %i | Mouse Pos Y: %i\nLMB: %i | RMB: %i\n", mouse.x, mouse.y, _mouseButtons.leftButton, _mouseButtons.rightButton);
		constexpr float sensivity = 0.05f;
		
		// x = roll, y = yaw, z = pitch
		//Vector3 camRot = _cam->transform.rotation.ToEuler();
		Vector3 camRot = _cam->lookDir;
		camRot.y += mouse.x * deltaTime * sensivity;
		camRot.z -= mouse.y * deltaTime * sensivity;
		//DebugPrintF("CamRot Y: %f | CamRot Z: %f\n", camRot.y, camRot.z);

		camRot.z = max(-VIEW_PITCH_CLAMP, camRot.z);
		camRot.z = min(VIEW_PITCH_CLAMP, camRot.z);
		
		if (camRot.y > XM_PI) { //if we do a full 360 on yaw.
			camRot.y -= XM_2PI; // Inverse the yaw axis to -360, basically.
		}
		else if (camRot.y < -XM_PI) {// if we go below -360 
			camRot.y += XM_2PI; // simply set us back to 360.
		}

		_cam->SetLookAtTrans(camRot);
	}

	if (_mouseButtons.rightButton == Mouse::ButtonStateTracker::PRESSED || HandleKeyPressed(keyToggleFlyCam)) {
		SetFlyCam(!_cam->flyCam);
	}
}

