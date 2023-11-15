#include "DX11Framework.h"
#include <string>
#include "Dxgidebug.h"

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

    _activeScene = new SceneManager();
    hr = _activeScene->Initialise(_renderManager);
    if (FAILED(hr)) return E_FAIL;

    _inputManager = new InputManager();
    _inputManager->SetRenderManager(_renderManager);
    _inputManager->SetSceneManager(_activeScene);
    _inputManager->SetFramework(this);

    _activeScene->LoadScene("Test");

    return hr;
}

DX11Framework::~DX11Framework()
{
    delete _renderManager;
    delete _windowManager;

    delete _activeScene;
    delete _inputManager;

}

void DX11Framework::RefreshScene() {
    delete _activeScene;

    HRESULT hr = S_OK;

    _activeScene = new SceneManager();
    hr = _activeScene->Initialise(_renderManager);
    if (FAILED(hr)) {
        throw new std::exception("Scene failed to load!");
        return;
    };

    _inputManager->SetSceneManager(_activeScene);

    _activeScene->LoadScene("Test");
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
    if (delay > maxDelay) {
        _inputManager->Update();
        delay = 0;
    }
    _activeScene->Update(deltaTime);
    _renderManager->Render(simpleCount, _activeScene);

    delay += deltaTime;
}