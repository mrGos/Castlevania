#include "CScene_EnterCastle.h"
#include "CSceneManager.h"
#include "CGameWorld.h"

void CScene_EnterCastle::init()
{
	GAMESTATE->IsLockingKeyBoard = true;
	SIMON->x = 552 - SIMON->width;
	SIMON->y = 283;
	SIMON->vx = 0.0002;
	SIMON->direction = Left;
	SIMON->isFlip = false;
	SIMON->IsLock = true;
	SIMON->IsWalkingCastle = true;
	SIMON->animId = MOVE;
	SIMON->SetState(SIMON_STATE::WALKING_CASTLE);
	SIMON->gy = 0;
	CAMERA->SetCornerBlock(0, 552);
	CAMERA->SetPosition(0, 0);
	GAMEWORLD->getCamera()->Lock();
	GAMEWORLD->getCamera()->x = 0;
	GAMEWORLD->getCamera()->y = 0;
	GAMESOUND->play(MUSIC_GAMESTART_PATH);
}

void CScene_EnterCastle::update(DWORD time, vector<LPGAMEOBJECT> *coObjects)
{
	if (!isFlagEnable) {
		SIMON->Update(time, coObjects);
		SIMON->updateLocation();
		if (SIMON->x <= FlagEnterCastle) {
			isFlagEnable = true;
			timeStartBack = GetTickCount();
			SIMON->animId = SIMON_STATE::ENTER;
		}
	}
	else {
		if (GetTickCount() - timeStartBack > timeDuringBack) {
			GAMESOUND->stop(MUSIC_GAMESTART_PATH);
			SIMON->Init();
			GAMEWORLD->getCamera()->UnLock();
			GAMESTATE->IsLockingKeyBoard = false;
			SCENEMANAGER->changeScene(new CScene_Intro(), true);
			VISUALFIGURES->IsStopTime = false;
		}
		else {
			SIMON->SetState(ENTER);
		}
	}
}

void CScene_EnterCastle::draw()
{
	enter_background->Draw(0, 0, D3DCOLOR_XRGB(255, 255, 255));
	SIMON->Render();
}

CScene_EnterCastle::CScene_EnterCastle()
{
	enter_background = SPRITES->Get(ENTER_BACKGROUND_ID);
}


CScene_EnterCastle::~CScene_EnterCastle()
{
}
