#pragma once
#include "CGameObject.h"



class Item : public CGameObject
{
private:


	DWORD timeStartDisappear;
	int timeDuringDisappear = 2000;

	void GenerateFiguresItem(int id);
	void RandomGenerateItem(bool isActive = true);
	void init();
public:
	bool IsEnableDisapear;

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void SetState(int state);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render();

	void updateProperties();
	//virtual void updateLocation();
	Item();
	Item(int itemID, float gravity = ITEM_GRAVITY);
	~Item();
};

typedef Item* LPITEM;