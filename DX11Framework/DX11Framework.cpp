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

    _objectManager = new ObjectManager();
    _objectManager->SetRenderManager(_renderManager);
    hr = InitCube(); // Renderer Class
    if (FAILED(hr)) return E_FAIL;
    
    return hr;
}

HRESULT DX11Framework::InitCube()
{
    Object* cube = new Cube();
    cube->SetName("Test Cube");
    _objectManager->AddObject(cube);
    return S_OK;
}



DX11Framework::~DX11Framework()
{
    delete _renderManager;
    delete _windowManager;
    delete _objectManager;
    delete _cube;

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

    _renderManager->Render(simpleCount, _objectManager);

}