#pragma once
#include "CScene.h"
#include "CGameObjectManager.h"
#include "Grid.h"

class CSceneManager : public CScene
{

private:
	CSceneManager();
	static CSceneManager * _instance;
	LPGAMEOBJECTMANAGER objManager;

	LPGRIDMANAGER gridManager;
public:
	static CSceneManager* getInstance();

	//LPGAMEOBJECTMANAGER getObjManager() { return this->objManager; }
	LPGRIDMANAGER getGridManager() { return this->gridManager; }

	void SetGridManager(LPGRIDMANAGER gridmanager) {
		gridManager = gridmanager;
	}

	void init();
	void update(DWORD time, vector<LPGAMEOBJECT> *coObjects = NULL);
	void draw();

	virtual ~CSceneManager();
};

