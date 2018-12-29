#pragma once
#include "CEnemy.h"

class CFishMan : public CEnemy
{
	int animId;

	float yOffsetStopJump = 485;
	bool IsJumping = false;
	bool IsAttack = false;
	bool IsRunning = false;

	int timeDuringAttack = 500;
	DWORD timeStartAttack;

	int timeDuringRuning = 2000;
	DWORD timeStartRuning;

	int count = 0;
	bool IsVisible = false;

	CFishMan();
public:

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);

	CFishMan(float x, float y, int direction);
	~CFishMan();
};

typedef CFishMan* LPFISHMAN;
