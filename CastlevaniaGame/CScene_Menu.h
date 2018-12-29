#pragma once
#include "CSprites.h"
#include "CScene.h"
#include "AppConfiguration.h"
#include "CGameState.h"
#include "CScene_EnterCastle.h"

class CScene_Menu : public CScene
{
public:
	LPSPRITE menu_background;

	void init();
	void update(DWORD time, vector<LPGAMEOBJECT> *coObjects = NULL);
	void draw();
	CScene_Menu();
	~CScene_Menu();
};

