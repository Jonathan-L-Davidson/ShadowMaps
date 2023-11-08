#include "Renderer.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "Camera.h"

Renderer::Renderer() {

}

Renderer::~Renderer() {
    DELETED3D(_immediateContext);
    DELETED3D(_device);
    DELETED3D(_dxgiFactory);
    DELETED3D(_frameBufferView);
    DELETED3D(_swapChain);
    DELETED3D(_rsDefault);
    DELETED3D(_rsWireframe);
    DELETED3D(_rsNoBackface);
    DELETED3D(_constantBuffer);
    DELETED3D(_depthStencilBuffer);
    DELETED3D(_depthStencilView);

    _activeRS = nullptr;
    _activeCam = nullptr;
}

HRESULT Renderer::Initialise() {
    HRESULT hr = S_OK;

    hr = CreateD3DDevice(); // Renderer class
    if (FAILED(hr)) return E_FAIL;

    hr = CreateSwapChainAndFrameBuffer(); // Renderer Class
    if (FAILED(hr)) return E_FAIL;

    hr = InitPipelineVariables(); // Renderer Class
    if (FAILED(hr)) return E_FAIL;

    return hr;
}

HRESULT Renderer::CreateD3DDevice()
{
    HRESULT hr = S_OK;

    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
    };

    ID3D11Device* baseDevice;
    ID3D11DeviceContext* baseDeviceContext;

    DWORD createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT | createDeviceFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &baseDevice, nullptr, &baseDeviceContext);
    if (FAILED(hr)) return hr;

    ///////////////////////////////////////////////////////////////////////////////////////////////

    hr = baseDevice->QueryInterface(__uuidof(ID3D11Device), reinterpret_cast<void**>(&_device));
    hr = baseDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext), reinterpret_cast<void**>(&_immediateContext));

    baseDevice->Release();
    baseDeviceContext->Release();

    ///////////////////////////////////////////////////////////////////////////////////////////////

    hr = _device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&_dxgiDevice));
    if (FAILED(hr)) return hr;

    IDXGIAdapter* dxgiAdapter;
    hr = _dxgiDevice->GetAdapter(&dxgiAdapter);
    hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&_dxgiFactory));
    dxgiAdapter->Release();

    return S_OK;
}

HRESULT Renderer::CreateSwapChainAndFrameBuffer()
{
    HRESULT hr = S_OK;

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
    swapChainDesc.Width = 0; // Defer to WindowWidth
    swapChainDesc.Height = 0; // Defer to WindowHeight
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //FLIP* modes don't support sRGB backbuffer
    swapChainDesc.Stereo = FALSE;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    swapChainDesc.Flags = 0;

    hr = _dxgiFactory->CreateSwapChainForHwnd(_device, _windowHandle, &swapChainDesc, nullptr, nullptr, &_swapChain);
    if (FAILED(hr)) return hr;

    ///////////////////////////////////////////////////////////////////////////////////////////////

    ID3D11Texture2D* frameBuffer = nullptr;

    hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&frameBuffer));
    if (FAILED(hr)) return hr;

    D3D11_RENDER_TARGET_VIEW_DESC framebufferDesc = {};
    framebufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; //sRGB render target enables hardware gamma correction
    framebufferDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

    hr = _device->CreateRenderTargetView(frameBuffer, &framebufferDesc, &_frameBufferView);

    D3D11_TEXTURE2D_DESC depthBufferDesc = {};
    frameBuffer->GetDesc(&depthBufferDesc);

    depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    _device->CreateTexture2D(&depthBufferDesc, nullptr, &_depthStencilBuffer);
    _device->CreateDepthStencilView(_depthStencilBuffer, nullptr, &_depthStencilView);

    frameBuffer->Release();


    return hr;
}

HRESULT Renderer::InitPipelineVariables()
{
    HRESULT hr = S_OK;

    //Default Rasterizer
    D3D11_RASTERIZER_DESC rasterizerDescDefault = {};
    rasterizerDescDefault.FillMode = D3D11_FILL_SOLID;
    rasterizerDescDefault.CullMode = D3D11_CULL_BACK;

    hr = _device->CreateRasterizerState(&rasterizerDescDefault, &_rsDefault);
    if (FAILED(hr)) return hr;


    //Wireframe Rasterizer
    D3D11_RASTERIZER_DESC rasterizerDescWireframe = {};
    rasterizerDescWireframe.FillMode = D3D11_FILL_WIREFRAME;
    rasterizerDescWireframe.CullMode = D3D11_CULL_NONE;

    hr = _device->CreateRasterizerState(&rasterizerDescWireframe, &_rsWireframe);
    if (FAILED(hr)) return hr;

    //Rasterizer
    D3D11_RASTERIZER_DESC rasterizerDescNoBackface = {};
    rasterizerDescNoBackface.FillMode = D3D11_FILL_SOLID;
    rasterizerDescNoBackface.CullMode = D3D11_CULL_NONE;

    hr = _device->CreateRasterizerState(&rasterizerDescNoBackface, &_rsNoBackface);
    if (FAILED(hr)) return hr;

    _immediateContext->RSSetState(_rsWireframe);

    //Viewport Values
    _viewport = { 0.0f, 0.0f, (float)_windowRect->x, (float)_windowRect->y, 0.0f, 1.0f };
    _immediateContext->RSSetViewports(1, &_viewport);

    //Constant Buffer
    D3D11_BUFFER_DESC constantBufferDesc = {};
    constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
    constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    hr = _device->CreateBuffer(&constantBufferDesc, nullptr, &_constantBuffer);
    if (FAILED(hr)) { return hr; }

    _immediateContext->VSSetConstantBuffers(0, 1, &_constantBuffer);
    _immediateContext->PSSetConstantBuffers(0, 1, &_constantBuffer);

    return S_OK;
}

void Renderer::Render(float simpleCount, SceneManager* sceneManager) {
    //Store this frames data in constant buffer struct
    XMFLOAT4X4 camView = _activeCam->GetView();
    XMFLOAT4X4 camProjection = _activeCam->GetProjection();
    _cbData.View = XMMatrixTranspose(XMLoadFloat4x4(&camView));
    _cbData.Projection = XMMatrixTranspose(XMLoadFloat4x4(&camProjection));
    
    _cbData.CameraPos = _activeCam->GetPosition();

    //Present unbinds render target, so rebind and clear at start of each frame
    float backgroundColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f };
    _immediateContext->OMSetRenderTargets(1, &_frameBufferView, _depthStencilView);
    _immediateContext->ClearRenderTargetView(_frameBufferView, backgroundColor);
    _immediateContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);

    //Write constant buffer data onto GPU
    D3D11_MAPPED_SUBRESOURCE mappedSubresource;

    ObjectManager* objManager = sceneManager->GetObjManager();
    for (Object* obj : objManager->GetObjects()) {
        Model* model = obj->GetModel();
        if (model) {
            model->SetupInput(_immediateContext);
            
            model->SetupTextures(_immediateContext);

            _cbData.AmbientLight = obj->GetColor();
            model->UpdateCBData(&_cbData);
            
            _cbData.World = XMMatrixTranspose(obj->transform->GetWorldMatrix());
            
            _immediateContext->Map(_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
            memcpy(mappedSubresource.pData, &_cbData, sizeof(_cbData));
            _immediateContext->Unmap(_constantBuffer, 0);
            
            model->Render(_immediateContext);
        }
    }

    //Present Backbuffer to screen
    _swapChain->Present(0, 0);
}