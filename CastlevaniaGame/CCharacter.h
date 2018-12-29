#pragma once
#include "CGameObject.h"

class CCharacter : public CGameObject
{
public:


	bool IsJumping = false;
	bool IsLanding = false;
	bool IsAttack = false;
	bool IsDown = false;
	bool IsRunning = false;
	bool IsAttackSubWeapon = false;


public:
	virtual void run() = 0;
	virtual void jump() = 0;
	virtual void stopRun() = 0;
	virtual void beDamaged(int HP);


	//virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	//virtual void Render() = 0;
	CCharacter();
	~CCharacter();
};

