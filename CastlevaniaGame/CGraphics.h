#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "CWindow_Screen.h"

class CGraphics
{
private:
	static CGraphics * _instance;
	HWND hWnd;

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 frameBuffer = NULL;
	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen

	//color
	int r = 255, g = 255, b = 255;

	/*ID3DXFont* dxfont;*/
	CGraphics(HWND hWnd);
public:
	static CGraphics * getInstance();

	void SetColor(int r, int g, int b);

	void Release();

	bool isInitDirect3D();
	bool isInitSpriteHandler();
	bool isSetFrameBuffer();
	bool isSetBackBuffer();

	bool InitFont();

	void Init();
	void Error();

	void BeginGraphics();
	void EndGraphics();
	void PresentBackBuffer() { d3ddv->Present(0, 0, 0, 0); }

	void PrintText(const char* str, int size, int x, int y, DWORD color);


	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return this->backBuffer; }
	LPDIRECT3DSURFACE9 GetFrameBuffer() { return this->frameBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	/*void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);*/
	void Draw(float x, float y, bool isFlip, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha);

	~CGraphics();
};

