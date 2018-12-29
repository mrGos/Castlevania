#pragma once
#include "CWeapon.h"

class CBoomerang :public CWeapon
{
	bool IsTurnBack = false;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void updateLocation();

	CBoomerang();
	~CBoomerang();
};

