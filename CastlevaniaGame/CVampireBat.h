#pragma once
#include "CEnemy.h"
#include <math.h> 

//fomula to update location to a destination points
//d = sqrt( (x-xo)^2 + (y-yo)^2 )
//hypotenuse = sqrt(2.squareEdge^2) --- square triangle

class CVampireBat : public CEnemy
{
	/*CGameState* gamestate;
	Camera* camera;*/

	bool IsIDLE, IsFlying, IsMoveToSide, IsAttack, IsUpdatePosY;
	int activeCombat = 0, activeFlying, activeSlowFlying;

	float distance, sq1, sq2, angle;
	float prevDistance = 0.0f;

	float posX_Intro = 5543.0f, posY_Intro = 146.0f;

	float leftArea, rightArea, topArea, bottomArea;
	float  yFlyingMiddle = 241.0f;

	int yFlyingCount;
	int MoveToSideCount = 1;

	float xAttackPlayer, xBack, yAttackPlayer, yBack;
	int attackCount = 1;

	LPANIMATION animIDLE;
	LPANIMATION animFly;

	int timeDuringIntro = 2000;
	int timeAttackHappen = 8000;

	DWORD timeStartIntro;
	DWORD timeStartAttack;


	void updateSquareEdge(float x1, float x2, float y1, float y2);
	void calculateDistance(float x1, float x2, float y1, float y2);
	void calculateAngle(float squareEdge, float hypotenuse);

	void updateDimension(float x1, float x2, float y1, float y2);
	void RetrievePlayerPosition(float  posX, float posY);
	CVampireBat();

public:
	bool IsActive, IsIntro;



	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);
	void updateLocation(DWORD dt);

	void startCombat();
	void setArea(float l, float t, float r, float b);


	CVampireBat(float x, float y, int direction);
	~CVampireBat();
};

typedef CVampireBat* LPVAMPIREBAT;