#include "CGraphics.h"


CGraphics* CGraphics::_instance = 0;
CGraphics::CGraphics(HWND hwnd)
{
	this->hWnd = hWnd;
	Init();
}

CGraphics * CGraphics::getInstance()
{
	if (_instance == 0)
		_instance = new CGraphics(WINDOW->getWindowHandler());
	return _instance;
}

void CGraphics::SetColor(int r, int g, int b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

void CGraphics::Release()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
	if (frameBuffer != NULL) frameBuffer->Release();
}

bool CGraphics::isInitDirect3D()
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = WINDOW->getWindowHandler();

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	/*d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;*/

	d3dpp.BackBufferWidth = BACK_WIDTH;
	d3dpp.BackBufferHeight = BACK_HEIGHT;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString("[ERROR] CreateDevice failed\n");
		return false;
	}


	OutputDebugString("[INFO] InitGame done;\n");
	return true;
}

bool CGraphics::isInitSpriteHandler()
{
	HRESULT hr = D3DXCreateSprite(d3ddv, &spriteHandler);
	return !FAILED(hr);
}

bool CGraphics::isSetFrameBuffer()
{
	HRESULT hr = d3ddv->CreateOffscreenPlainSurface(SCREEN_WIDTH,
		SCREEN_HEIGHT,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&frameBuffer,
		0);
	return !FAILED(hr);
}

bool CGraphics::isSetBackBuffer()
{
	HRESULT hr = d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO,
		&backBuffer);
	return !FAILED(hr);
}

bool CGraphics::InitFont()
{
	/*dxfont = NULL;

	AddFontResourceEx(GAME_FONT, FR_PRIVATE, NULL);
	HRESULT result = D3DXCreateFont(
		d3ddv, 20, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, "Press Start", &dxfont);

	if (!SUCCEEDED(result))
		return false;*/
	return true;
}

void CGraphics::Init()
{
	if (!isInitDirect3D() || !isInitSpriteHandler() || !isSetBackBuffer() || !isSetFrameBuffer() /*|| !InitFont()*/)
		Error();
}

void CGraphics::Error()
{
	MessageBox(hWnd, "failed to initialize Graphics", "Error", MB_ICONERROR);
	PostQuitMessage(0);
}

void CGraphics::BeginGraphics()
{
	HRESULT hr = d3ddv->BeginScene();
	HRESULT hr1 = spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	d3ddv->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 50, 10), 1.0f, 0);
	if (FAILED(hr) || FAILED(hr1))
	{
		MessageBox(0, "Failed to Start Scene", "Error", MB_ICONERROR);
		PostQuitMessage(0);
	}
}

void CGraphics::EndGraphics()
{
	HRESULT hr1 = spriteHandler->End();
	HRESULT hr = d3ddv->EndScene();
	if (FAILED(hr) || FAILED(hr1))
	{
		MessageBox(0, "Failed to End Scene ", "Loi", MB_ICONERROR);
		PostQuitMessage(0);
	}
}

void CGraphics::PrintText(const char * str, int size, int x, int y, DWORD color)
{
	/*ID3DXFont* dxfont;
	RECT textbox;
	AddFontResourceEx(GAME_FONT, FR_PRIVATE, NULL);
	SetRect(&textbox, x, y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

	D3DXCreateFont(
		d3ddv, size, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, "Press Start", &dxfont);
	dxfont->DrawTextA(NULL,
		str,
		strlen(str),
		&textbox,
		DT_LEFT,
		color);

	dxfont->Release();*/
}


void CGraphics::Draw(float x, float y, bool isFlip, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha)
{

	D3DXVECTOR3 p(x, y, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	D3DXMATRIX oldTransform;
	spriteHandler->GetTransform(&oldTransform);

	D3DXMATRIX newTransform;
	D3DXVECTOR2 center = D3DXVECTOR2(x + (right - left) / 2, y + (bottom - top) / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(isFlip ? -1 : 1, 1);

	D3DXMatrixTransformation2D(&newTransform, &center, 0.0f, &rotate, NULL, 0.0f, NULL);

	D3DXMATRIX finalTransform = newTransform * oldTransform;
	spriteHandler->SetTransform(&finalTransform);
	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, this->r, this->g, this->b));
	spriteHandler->SetTransform(&oldTransform);

	//D3DXMatrixScaling(&matScale, 1.0f, 1.0f, 1.0f);
	//spriteHandler->SetTransform(&matScale);

}


CGraphics::~CGraphics()
{
	//dxfont->Release();
	this->Release();
}
