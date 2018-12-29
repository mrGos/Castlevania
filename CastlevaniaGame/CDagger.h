#pragma once
#include "CWeapon.h"
class CDagger : public CWeapon
{
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);
	//void updateLocation();

	CDagger();
	~CDagger();
};

