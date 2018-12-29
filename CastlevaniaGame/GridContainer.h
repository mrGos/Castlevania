#pragma once
#include "CGameObject.h"

class GridContainer :public CGameObject {


public:
	vector<LPGAMEOBJECT>listObjectInGrid;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();

	void SetListObject(vector<LPGAMEOBJECT> listObj);
	int Size() { return listObjectInGrid.size(); }
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Add(LPGAMEOBJECT gobj) { listObjectInGrid.push_back(gobj); }
	void Clear() { listObjectInGrid.clear(); }
	void RemoveAllObject();
	bool isOutOfCamera();


	GridContainer(float x, float y);
	~GridContainer();
};
typedef GridContainer* LPGRIDCONTAINER;
