#pragma once
#include "CWeapon.h"

class CWhip : public CWeapon
{
private:

	static CWhip* _instance;
	void updateProperty();
public:

	static CWhip* getInstance();

	int curAnim = 0;


	bool IsEnable = false;
	bool IsAttack = false;

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void updateLocation();
	float  PosXPrepare();
	float  PosXAttack();


	CWhip();
	~CWhip();
};

typedef CWhip* LPWHIP;