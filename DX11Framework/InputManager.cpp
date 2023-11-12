#include "InputManager.h"
#include "Renderer.h"
#include "SceneManager.h"
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

void InputManager::HandleSceneKeys() {
}

void InputManager::HandleMiscKeys() {
}

