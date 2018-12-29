#pragma once
#include "CEnemy.h"

class CGhost :public CEnemy
{
	CGhost();
public:

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	CGhost(float x, float y, int direction);
	~CGhost();
};

typedef CGhost* LPGHOST;