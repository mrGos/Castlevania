#pragma once
#include "CScene.h"
#include "CGameState.h"
#include "CScene_Intro.h"
class CScene_EnterCastle : public CScene
{
	int FlagEnterCastle = 260;
	bool isFlagEnable = false;

	int timeDuringBack = 2500;
	DWORD timeStartBack;
public:
	LPSPRITE enter_background;

	void init();
	void update(DWORD time, vector<LPGAMEOBJECT> *coObjects = NULL);
	void draw();

	CScene_EnterCastle();
	~CScene_EnterCastle();
};

