#pragma once
#include "CEnemy.h"

class CDog : public CEnemy
{
	CDog();
	int animId;

	bool IsJumping = false;
	int count = 0;
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);

	CDog(float x, float y, int direction);
	~CDog();
};
typedef CDog* LPDOG;
