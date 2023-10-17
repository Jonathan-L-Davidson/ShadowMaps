#pragma once

#ifndef RENDERER_H
#define RENDERER_H
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "Structures.h"
#include "model.h"

class Camera;
class ObjectManager;

class Renderer
{
public:
	Renderer();
	~Renderer();
	HRESULT Initialise();

	void SetWindowRect(Rect* rect) { _windowRect = rect; };
	void SetWindowInstance(HWND hwnd) { _windowHandle = hwnd; };
	void SetCamera(Camera* cam) { _cam = cam; };

	ID3D11DeviceContext* GetDeviceContext() { return _immediateContext; };
	ID3D11Device* GetDevice() { return _device; };

	void Render(float simpleCount, ObjectManager* objManager);
private:
	Rect* _windowRect;

	// Initialisers
	HRESULT CreateD3DDevice();
	HRESULT CreateSwapChainAndFrameBuffer();
	HRESULT InitPipelineVariables();
	HRESULT InitRunTimeData();

	ID3D11DeviceContext* _immediateContext = nullptr;
	ID3D11Device* _device;
	IDXGIDevice* _dxgiDevice = nullptr;
	IDXGIFactory2* _dxgiFactory = nullptr;
	ID3D11RenderTargetView* _frameBufferView = nullptr;
	IDXGISwapChain1* _swapChain;
	D3D11_VIEWPORT _viewport;

	ID3D11RasterizerState* _rasterizerState;
	ID3D11Buffer* _constantBuffer;
	ID3D11Texture2D* _depthStencilBuffer;
	ID3D11DepthStencilView* _depthStencilView;

	HWND _windowHandle;

	ConstantBuffer _cbData;
	XMFLOAT4X4 _World;

	Camera* _cam;
	XMFLOAT4X4 _View;
	XMFLOAT4X4 _Projection;	

};

#endif