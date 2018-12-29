#pragma once
#include "CGameObject.h"

class CEnemy : public CGameObject
{
public:
	int timeDuringBurn = TIME_DURING_BURN;
	DWORD timeStartBurn;

	int untouchableCount = 0;
	DWORD lastUntouchableTime;
	int timeDuringUntouchable = 500;

	bool IsActivated;
	bool IsBreak;

	void UpdateState();
	void updateFlipImage();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);

	CEnemy();
	~CEnemy();
};

typedef CEnemy* LPENEMY;