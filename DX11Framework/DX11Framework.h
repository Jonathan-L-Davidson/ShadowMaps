#pragma once

#include <windows.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <list>
#include "Model.h"
#include "Renderer.h"
#include "WindowManager.h"
//#include <wrl.h>

using namespace DirectX;
//using Microsoft::WRL::ComPtr;


class DX11Framework
{
	int _windW = 1280;
	int _windH = 768;

	D3D11_VIEWPORT _viewport;

	Renderer* _renderManager;
	WindowManager* _windowManager;
public:
	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitCube();
	~DX11Framework();
	void Update();
};