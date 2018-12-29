#pragma once
#include "CWeapon.h"

class CHollyWater : public CWeapon
{
	LPSPRITE water;
	LPANIMATION animBurn;

	DWORD timeStartFlame;
	int timeDuringFlame = 800;
	bool isFlame = false;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	CHollyWater();
	~CHollyWater();
};

