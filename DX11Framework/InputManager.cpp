#include "InputManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include <winuser.h>

void InputManager::Update() {

	HandleRenderKeys();
	HandleMovementKeys();
	HandleSceneKeys();
	HandleMiscKeys();
}

void InputManager::HandleRenderKeys() {
	if (GetAsyncKeyState(keyWireframeToggle) & 0x8000) {

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

}

void InputManager::HandleSceneKeys() {
}

void InputManager::HandleMiscKeys() {
}

