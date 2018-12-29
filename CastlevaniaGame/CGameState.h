#pragma once
#include "AppConfiguration.h"
#include "CStage.h"
#include <string>
class CGameState
{
private:
	static CGameState * _instance;
	CGameState();
public:

	bool IsStartGame = false;
	bool IsLockingKeyBoard = false;

	int gameLevel = 0;
	int gameBossHP = SIMON_FULL_HP;

	bool IsStopWatch = false;
	bool IsCrossActivated = false;

	bool IsCheckPoint = false;
	bool IsGameEnd = false, IsGameWin = false;

	std::string currentMusic = "";

	LPSTAGE stage;

	static CGameState* getInstance();
	~CGameState();
};

