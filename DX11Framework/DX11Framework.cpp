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

    _gameTimer = new Timer();

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
    float deltaTime = _gameTimer->GetDelta();
    _gameTimer->Tick();

    while (accumilator >= FPS60) {
        std::string debug = std::to_string(accumilator) + "\n";
        OutputDebugStringA(debug.c_str());
        
        _inputManager->Update();
        _activeScene->Update(deltaTime);
        accumilator = 0;
    }

    _renderManager->Render(deltaTime, _activeScene);

    accumilator += deltaTime;
}