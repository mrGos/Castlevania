#pragma once
#include "CCharacter.h"
#include "EnumCommon.h"
#include "Item.h"
#include "Static.h"
#include <string>
#include "CWhip.h"
#include "GameSound.h"
#include "CSceneManager.h"

class CSimon : public CCharacter
{

	static CSimon* _instance;

	bool FlagStairDownLTR = false;

	DWORD lastAttackTime;
	int timeDuringAttack = SIMON_TIME_DURING_ATTACK;

	int untouchableCount = 0;
	DWORD lastUntouchableTime;
	int timeDuringUntouchable = 3000;

	int prepareEndGameCount = 0;
	bool IsReborn, IsPrepareEndGame;
	DWORD timeStartEndGame, timeStartReborn;
	int timeDuringEndGame = 2000, timeDuringReborn = 2000;

	LPWHIP _weapon;

	void walk();
	bool IsEnter = false;

	CSceneManager* sceneManager;
	CAnimations* animations;

	void GenerateSubWeaponThrow();

	//Simon die handle
	void DieHandle();
	//after defeating boss
	bool IsBossDefeated;
	DWORD timeStartPrepareCheckpoint;
	int timeDuringPrepareCheckpoint = 6000;
	void BossDefeatedHandle();

public:
	float xStairOffset = 0;
	float yDeathFlag = 384.0f;

	int animId = 0;
	int attackType;

	bool IsStairing = false;
	bool IsAbleStairing = false;
	int typeStairing = ObjectSpecial::STAIR_STOP;

	DWORD lastStopWatchTime;
	int timeDuringStopWatch = 2000;

	DWORD lastCrossActivatedTime;
	int timeDuringCrossActivated = 1000;

	bool IsLock = false;
	bool IsWalkingCastle = false;
	bool isRepeatAnim = true;
	bool IsUnTouchable = false;

	CSimon();
	void Init();
	void SetAnimID();
	static CSimon* getInstance();

	LPWHIP getWeapon() { return this->_weapon; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void run();
	void jump();
	void stopRun();
	void attack();
	void stairUp();
	void stairDown();

	void RetrieveFiguresFromItem(LPITEM item);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~CSimon();
};

