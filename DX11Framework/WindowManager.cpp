#include "WindowManager.h"

#include "Mouse.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN: // Easier way to close the application
        if (wParam == VK_ESCAPE) {
            PostMessage(hWnd, WM_CLOSE, 0, 0);
            break;
        }

    // DirectXTK handles all these forms of messages.
    case WM_INPUT:
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MOUSEWHEEL:
    case WM_XBUTTONDOWN:
    case WM_XBUTTONUP:
    case WM_MOUSEHOVER:
        DirectX::Mouse::ProcessMessage(message, wParam, lParam);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

WindowManager::~WindowManager() {
    delete _windowRect;
}

HRESULT WindowManager::Initialise(HINSTANCE hInstance, int nCmdShow, int windX, int windY) {
    const wchar_t* windowName = L"DX11Framework";

    _windowRect = new Rect();
    _windowRect->x = windX;
    _windowRect->y = windY;

    WNDCLASSW wndClass;
    wndClass.style = 0;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = 0;
    wndClass.hIcon = 0;
    wndClass.hCursor = 0;
    wndClass.hbrBackground = 0;
    wndClass.lpszMenuName = 0;
    wndClass.lpszClassName = windowName;

    RegisterClassW(&wndClass);

    _windowHandle = CreateWindowExW(0, windowName, windowName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
        _windowRect->x, _windowRect->y, nullptr, nullptr, hInstance, nullptr);

    return S_OK;
}