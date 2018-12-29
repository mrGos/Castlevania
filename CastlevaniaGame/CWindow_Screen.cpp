#include "CWindow_Screen.h"


CWindow_Screen* CWindow_Screen::_instance = 0;
CWindow_Screen::CWindow_Screen()
{
}

CWindow_Screen * CWindow_Screen::getInstance()
{
	if (_instance == 0)
		_instance = new CWindow_Screen();
	return _instance;
}


LRESULT CWindow_Screen::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;*/

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

ATOM CWindow_Screen::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = CLASS_NAME;
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //Set clear background

	//register window class
	//đăng ký lớp cửa sổ
	return RegisterClassEx(&wcex);;

}

void CWindow_Screen::Init_WindowHandler(HINSTANCE hInstance, int nCmdShow)
{
	MyRegisterClass(hInstance);

	/*HWND hWnd = CreateWindowEx(CLASS_NAME, TITLE_STR, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, hInstance, NULL);*/

		//create window params
	HWND hWnd = CreateWindow(
		CLASS_NAME,			//window class
		TITLE_STR,			//title bar
		//WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
		WS_OVERLAPPEDWINDOW,

		//window style
		CW_USEDEFAULT,		//posScreen x
		CW_USEDEFAULT,		//posScreen y
		SCREEN_WIDTH,		//Screen width
		SCREEN_HEIGHT,		//Screen height
		0,				//parent window
		0,				//menu	
		hInstance,			//app instance
		NULL);				//window parameters

	if (!hWnd)
	{
		return;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	this->hWnd = hWnd;
}

HWND CWindow_Screen::getWindowHandler()
{
	return hWnd;
}

CWindow_Screen::~CWindow_Screen()
{
}
