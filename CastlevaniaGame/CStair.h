#pragma once
#include "CGameObject.h"

class CStair :public CGameObject
{
	CStair();
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	CStair(int x, int y, int id, int width = 64, int height = 32);
	~CStair();
};

