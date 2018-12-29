#pragma once
#include "CGameObject.h"

class Static :public CGameObject
{
	int timeDuringBurn = TIME_DURING_BURN;
	DWORD timeStartBurn;

	int itemId = -1;

	bool IsBreak = false;

	void generateItem();
public:

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);

	void SetItem(int itemId);
	Static();
	~Static();
};

typedef Static* LPSTATIC;
