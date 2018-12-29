#pragma once
#include <d3dx9.h>
#include "CGraphics.h"
#include "CWindow_Screen.h"
#include "AppConfiguration.h"
#include "CGameWorld.h"

class CGamePanel
{
	CGameWorld* gamworld;
	CGamePanel();
public:

	CGamePanel(HINSTANCE, int);
	~CGamePanel();

	void GameLoop();
};

