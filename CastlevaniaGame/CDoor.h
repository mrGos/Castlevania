#pragma once
#include "CGameObject.h"
class CDoor : public CGameObject
{
	LPANIMATION AnimDoorClose;
	LPANIMATION AnimDoorOpenActive;
	LPANIMATION AnimDoorCloseActive;

	CDoor();

	bool IsOpen = false;

	bool IsUpdatePlayerState = false;


public:
	float xOffsetCameraAfterUpdate = 0;
	float xOffsetPlayerAfterUpdate = 0;

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);

	CDoor(float posx, float posy);
	~CDoor();
};

typedef CDoor* LPDOOR;