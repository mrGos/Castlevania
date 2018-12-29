#pragma once
#include <Windows.h>
#include "AppConfiguration.h"

class CWindow_Screen
{
private:
	HWND hWnd;

	static CWindow_Screen* _instance;
	CWindow_Screen(void);
	ATOM MyRegisterClass(HINSTANCE hInstance);
public:
	static CWindow_Screen* getInstance();

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	void Init_WindowHandler(HINSTANCE hInstance, int nCmdShow);
	HWND getWindowHandler();

	~CWindow_Screen(void);
};

