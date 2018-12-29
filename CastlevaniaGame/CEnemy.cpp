#include "CEnemy.h"
#include "EnumCommon.h"
#include "CGameState.h"

void CEnemy::UpdateState()
{
	if (IsBreak) {
		if (GetTickCount() - timeStartBurn >= timeDuringBurn)
		{
			SetState(ObjectState::DIE);
		}
	}

	/*if (this->isObjectOutOfCameraView())
		SetState(ObjectState::DIE);*/

	if (GetHP() <= 0 && !IsBreak) {
		timeStartBurn = GetTickCount();
		IsBreak = true;
		dx = 0;
		dy = 0;
		gy = 0;
		vx = 0;
		vy = 0;
		SetState(ObjectState::BURN);
	}
	updateFlipImage();
	/*if (vx > 0)
		isFlip = true;
	else if (vx < 0)
		isFlip = false;*/
}

void CEnemy::updateFlipImage()
{
	(direction == Right) ? isFlip = true : isFlip = false;
}

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GAMESTATE->IsCrossActivated)
		SetState(ObjectState::DIE);
}

CEnemy::CEnemy()
{
}


CEnemy::~CEnemy()
{
}
