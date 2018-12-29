#pragma once
#include "AppConfiguration.h"
#include "CSprites.h"
#include "CGameObject.h"


class CScene
{
private:

public:
	static CScene* curScene;


	static void changeScene(CScene* scene, bool clean = true);
	virtual void init() = 0;
	virtual void update(DWORD time = 0, vector<LPGAMEOBJECT> *coObjects = NULL) = 0;
	virtual void draw() = 0;

	CScene(void);
	~CScene(void);
};

