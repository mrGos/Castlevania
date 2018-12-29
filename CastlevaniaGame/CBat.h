#pragma once
#include "CEnemy.h"

class CBat :public CEnemy
{
	int yFlyOffsetBottom = 0;
	int yFlyOffsetTop = 0;

	int flyYPos = 1;
	int directy = 1;

	CBat();
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void updateLocation();

	CBat(float x, float y, int direction);
	~CBat();
};
typedef CBat* LPBAT;
