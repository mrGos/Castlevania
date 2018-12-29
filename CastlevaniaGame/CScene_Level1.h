#pragma once
#include "CScene.h"
#include "Item.h"
#include "BackgroundMap.h"
#include "Static.h"
#include "CVampireBat.h"
#include "CGhost.h"
#include "CDog.h"
#include "CBat.h"
#include "CFishMan.h"

class CScene_Level1 : public CScene
{
	LPBACKGROUNDMAP bgmap;


	float yFlagBasementStairDown = 310;
	float yFlagBasementStairUp = 426;



	float xBoosFlag = 5375;


	LPVAMPIREBAT boss;
public:
	bool FlagDownBasement = false;
	bool FlagAboveBasement = true;

	void init();
	void update(DWORD time, vector<LPGAMEOBJECT> *coObjects = NULL);
	void draw();

	CScene_Level1();
	~CScene_Level1();
};

