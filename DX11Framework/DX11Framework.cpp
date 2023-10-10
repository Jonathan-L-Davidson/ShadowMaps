#include "DX11Framework.h"
#include <string>

//#define RETURNFAIL(x) if(FAILED(x)) return x;


HRESULT DX11Framework::Initialise(HINSTANCE hInstance, int nShowCmd)
{
    HRESULT hr = S_OK;

    // WindowManager Init
    _windowManager = new WindowManager();
    hr = _windowManager->Initialise(hInstance, nShowCmd, _windW, _windH); // Application class
    if (FAILED(hr)) return E_FAIL;

    // RenderManager Init
    _renderManager = new Renderer();
    _renderManager->SetWindowRect(_windowManager->GetWindRect());
    _renderManager->SetWindowInstance(_windowManager->GetHandle());
    hr = _renderManager->Initialise();
    if (FAILED(hr)) return E_FAIL;

    // ModelManager Init
    _modelManager = new ModelManager();
    _modelManager->SetRenderManager(_renderManager);
    _modelManager->Initialise();

    // ObjManager Init
    _objectManager = new ObjectManager();
    _objectManager->SetRenderManager(_renderManager);
    _objectManager->SetModelManager(_modelManager);
    hr = InitCube(); // Renderer Class
    if (FAILED(hr)) return E_FAIL;
    
    // Camera Init
    XMFLOAT3X3 CamPos = XMFLOAT3X3(0, 0, -10.0f, // eye
        0, 0, 0, // at
        0, 1, 0); // up

    _cam = new Camera(CamPos);
    _renderManager->SetCamera(_cam);

    return hr;
}

HRESULT DX11Framework::InitCube()
{
    Object* cube = new Cube();
    cube->SetName("Test Cube");
    _objectManager->AddObject(cube, XMFLOAT3(0.0f, 3.0f, 5.0f));

    _pyramid = new Pyramid();
    _pyramid->SetName("Test Pyramid");
    _objectManager->AddObject(_pyramid, XMFLOAT3(-3.0f, 0.0f, 5.0f));

    return S_OK;
}



DX11Framework::~DX11Framework()
{
    delete _renderManager;
    delete _windowManager;
    delete _modelManager;
    delete _objectManager;

    delete _pyramid;
    delete _cam;
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

    /* // Just some code experimenting with camera coordinates.
    // Camera update thing.
    XMFLOAT3 eye = _cam->GetPosition();
    eye.x += 4 * deltaTime;
    XMFLOAT3 at = _cam->GetAt();
    at.x = eye.x + 1;
    _cam->SetAt(at);
    _cam->SetPosition(eye);
    */

    //_cam->LookAt(_pyramid->GetPosition());

    // Normal standard loop.
    _objectManager->Update(deltaTime);
    _renderManager->Render(simpleCount, _objectManager);

}