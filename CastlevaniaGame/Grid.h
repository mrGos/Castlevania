#pragma once
#include "GridContainer.h"


class GridManager
{

public:
	vector <LPGRIDCONTAINER>listGridContainer;

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();

	void SetListObjectInCamera(vector<LPGAMEOBJECT> listObjInCamera);
	void AddContainer(LPGRIDCONTAINER gobj);
	void AddObject(LPGAMEOBJECT obj);
	void Clear();
	void RemoveAll();

	void SetCoObjects(vector<LPGAMEOBJECT> &l);

	GridManager();
	GridManager(int n);
	~GridManager();
};
typedef GridManager* LPGRIDMANAGER;

