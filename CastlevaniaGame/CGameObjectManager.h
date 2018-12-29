#pragma once
#include "CGameObject.h"
#include <algorithm>
#include "EnumCommon.h"
#include "CVisualFigures.h"

class CGameObjectManager
{

public:
	vector<LPGAMEOBJECT> listGameObjects;

	void Add(LPGAMEOBJECT obj);
	void Remove(LPGAMEOBJECT obj);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	CGameObjectManager();
	~CGameObjectManager();
};

typedef CGameObjectManager* LPGAMEOBJECTMANAGER;