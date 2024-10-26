#pragma once

#define FPS60 1.0f/60.0f

#include <windows.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <list>
#include "Renderer.h"
#include "WindowManager.h"
#include "sceneManager.h"
#include "InputManager.h"
#include "Timer.h"
//#include <wrl.h>

using namespace DirectX;
//using Microsoft::WRL::ComPtr;


class DX11Framework
{
public:
	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);
	~DX11Framework();
	void Update();

	void RefreshScene();
private:
	int _windW = 1920;
	int _windH = 1080;

	D3D11_VIEWPORT _viewport;

	Renderer* _renderManager;
	WindowManager* _windowManager;

	SceneManager* _activeScene;

	InputManager* _inputManager;

	Timer* _gameTimer;

	float accumilator;
	float delay = 0.0f;
	float maxDelay = 0.05f;
};