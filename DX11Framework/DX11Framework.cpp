#include "DX11Framework.h"
#include <string>

//#define RETURNFAIL(x) if(FAILED(x)) return x;


HRESULT DX11Framework::Initialise(HINSTANCE hInstance, int nShowCmd)
{
    HRESULT hr = S_OK;

    _windowManager = new WindowManager();
    hr = _windowManager->Initialise(hInstance, nShowCmd, _windW, _windH); // Application class
    if (FAILED(hr)) return E_FAIL;

    _renderManager = new Renderer();
    _renderManager->SetWindowRect(_windowManager->GetWindRect());
    _renderManager->SetWindowInstance(_windowManager->GetHandle());
    hr = _renderManager->Initialise();
    if (FAILED(hr)) return E_FAIL;

    hr = InitCube(); // Renderer Class
    if (FAILED(hr)) return E_FAIL;
    
    return hr;
}

HRESULT DX11Framework::InitCube()
{
    //std::vector<SimpleVertex> VertexData =
    //{
    //    //Position                     //Color             
    //    { XMFLOAT3(-1.00f,  1.00f, 0), XMFLOAT4(1.0f,  0.0f, 0.0f,  0.0f)},
    //    { XMFLOAT3(1.00f,  1.00f, 0),  XMFLOAT4(0.0f,  1.0f, 0.0f,  0.0f)},
    //    { XMFLOAT3(-1.00f, -1.00f, 0), XMFLOAT4(0.0f,  0.0f, 1.0f,  0.0f)},
    //    { XMFLOAT3(1.00f, -1.00f, 0),  XMFLOAT4(1.0f,  1.0f, 1.0f,  0.0f)},
    //    { XMFLOAT3(-1.00f,  1.00f, 2.00f), XMFLOAT4(1.0f,  1.0f, 0.0f,  0.0f)},
    //    { XMFLOAT3(1.00f,  1.00f, 2.00f),  XMFLOAT4(0.0f,  1.0f, 1.0f,  0.0f)},
    //    { XMFLOAT3(-1.00f, -1.00f, 2.00f), XMFLOAT4(1.0f,  0.0f, 1.0f,  0.0f)},
    //    { XMFLOAT3(1.00f, -1.00f, 2.00f),  XMFLOAT4(0.5f,  0.5f, 1.0f,  0.0f)},
    //};

    //std::vector<WORD> IndexData =
    //{
    //    //Indices
    //    0,1,2,
    //    2,1,3,
    //    
    //    5,7,3,
    //    5,3,1,

    //    7,5,4,
    //    6,7,4,

    //    6,4,0,
    //    0,2,6,

    //    5,1,4,
    //    4,1,0,

    //    3,7,6,
    //    3,6,2,

    //};

    //_cube = new Model(_renderManager->GetDevice(), VertexData, IndexData);
    //Shader shaders = _renderManager->GetShaders();
    //_cube->SetVertexShader(shaders.vertexShader);
    //_cube->SetPixelShader(shaders.pixelShader);

    return S_OK;
}



DX11Framework::~DX11Framework()
{
    delete _renderManager;
}


void DX11Framework::Update()
{
    //Static initializes this value only once    
    static ULONGLONG frameStart = GetTickCount64();

    ULONGLONG frameNow = GetTickCount64();
    float deltaTime = (frameNow - frameStart) / 1000.0f;
    frameStart = frameNow;

    static float simpleCount = 0.0f;
    simpleCount += deltaTime;

    _renderManager->Render(simpleCount);

}