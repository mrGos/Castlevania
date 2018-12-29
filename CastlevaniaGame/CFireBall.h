#pragma once
#include "CEnemy.h"

class CFireBall : public CEnemy
{
	CFireBall();
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	CFireBall(float x, float y, int direction);
	~CFireBall();
};

typedef CFireBall* LPFIREBALL;
