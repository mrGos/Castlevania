#pragma once
#include "CGameObject.h"
#include "CSprites.h"
class CGround : public CGameObject
{
	LPSPRITE sprite;
public:
	bool IsBreak = false;
	bool IsAbleBreak = false;
	bool IsStairFlag = false;
	bool IsItem = false;

	int itemID = 0;

	bool IsNoneRender;
	CGround(int groundNum = 1, bool IsAbleBreak = false, bool IsStairFlag = false, bool IsItem = false, int itemID = 0);
	CGround(float x, float y, int width, int height, bool IsNoneRender);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	~CGround();
};

