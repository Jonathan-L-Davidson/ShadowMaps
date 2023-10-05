#pragma once

#if !defined(WINDOWMANAGER_H)
#define WINDOWMANAGER_H
#include <d3d11_3.h>
#include "Structures.h"

class WindowManager
{
public:
	WindowManager() {};
	~WindowManager();
	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow, int windX, int windY);
	Rect* GetWindRect() { return _windowRect; };
	static HWND& GetHandle() { return _windowHandle; };
private:
	Rect* _windowRect;
	static HWND _windowHandle;
};

#endif

