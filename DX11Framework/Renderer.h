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
class SceneManager;

using namespace DirectX;

class Renderer
{
public:
	Renderer();
	~Renderer();
	HRESULT Initialise();

	void SetWindowRect(Rect* rect) { _windowRect = rect; };
	Rect* GetWindowRect() { return _windowRect; };
	void SetWindowInstance(HWND hwnd) { _windowHandle = hwnd; };
	HWND GetWindowInstance() { return _windowHandle; };
	void SetCamera(Camera* cam) { _activeCam = cam; };

	D3D11_VIEWPORT GetViewPort() { return _viewport; };

	ID3D11DeviceContext* GetDeviceContext() { return _immediateContext; };
	ID3D11Device* GetDevice() { return _device; };

	void Render(float simpleCount, SceneManager* sceneManager);
	void SwapRS(const char input);
private:
	Rect* _windowRect;

	// Initialisers
	HRESULT CreateD3DDevice();
	HRESULT CreateSwapChainAndFrameBuffer();
	HRESULT InitPipelineVariables();

	ID3D11DeviceContext* _immediateContext = nullptr;
	ID3D11Device* _device;
	IDXGIDevice* _dxgiDevice = nullptr;
	IDXGIFactory2* _dxgiFactory = nullptr;
	ID3D11RenderTargetView* _frameBufferView = nullptr;
	IDXGISwapChain1* _swapChain;
	D3D11_VIEWPORT _viewport;

	ID3D11ShaderResourceView* _shadowBuffer;

	ID3D11RasterizerState* _activeRS;
	ID3D11RasterizerState* _rsDefault;
	ID3D11RasterizerState* _rsWireframe;
	ID3D11RasterizerState* _rsNoBackface;
	ID3D11Buffer* _constantBuffer;
	ID3D11Texture2D* _depthStencilBuffer;
	ID3D11DepthStencilView* _depthStencilView;

	HWND _windowHandle;

	ConstantBuffer _cbData;
	XMFLOAT4X4 _World;

	Camera* _activeCam;
};

#endif