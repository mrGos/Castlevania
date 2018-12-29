#pragma once
#include "CGameObject.h"

class CWeapon :public CGameObject
{
public:

	void attackEnemy(LPGAMEOBJECT &enemyObj);
	CWeapon();
	~CWeapon();
};

