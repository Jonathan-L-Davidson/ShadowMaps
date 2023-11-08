#pragma once

#include <windows.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <list>
#include "Renderer.h"
#include "WindowManager.h"
#include "sceneManager.h"
#include "InputManager.h"

//#include <wrl.h>

using namespace DirectX;
//using Microsoft::WRL::ComPtr;


class DX11Framework
{
public:
	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);
	~DX11Framework();
	void Update();
private:
	int _windW = 1280;
	int _windH = 768;

	D3D11_VIEWPORT _viewport;

	Renderer* _renderManager;
	WindowManager* _windowManager;

	SceneManager* _activeScene;

	InputManager* _inputManager;

	float delay = 0.0f;
	float maxDelay = 0.05f;
};