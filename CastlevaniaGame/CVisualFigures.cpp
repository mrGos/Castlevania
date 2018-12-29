#include "CVisualFigures.h"
#include "CSimon.h"
#include "CGameState.h"
#include "CommonFunction.h"


CVisualFigures* CVisualFigures::_instance = 0;

CVisualFigures * CVisualFigures::getInstance()
{
	if (_instance == 0)
		_instance = new CVisualFigures();
	return _instance;
}

void CVisualFigures::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

void CVisualFigures::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (!IsCheckPoint) {
		if (GetTickCount() - timeStartCount >= timeDuringCount && !GAMESTATE->IsStopWatch && !IsStopTime) {
			if (timeCount <= 0) {
				timeCount = 0;
			}
			else {
				timeCount -= 1;
			}
			timeStartCount = GetTickCount();
		}
	}
	else if (IsCheckPoint && !IsChangeScene) {
		//handle checkPoint after defeating boss
		if (GetTickCount() - timeStartCount >= timeDuringCount) {
			if (timeCount > 0) {
				timeCount -= 1;
			}
			else {
				if (SIMON->GetSP() > 0) {
					SIMON->SetSP(SIMON->GetSP() - 1);
				}
				else {
					//time start win game or change scene
					IsChangeScene = true;
					timeStartPrepareChangeScene = GetTickCount();
				}
			}
			SIMON->SetScore(SIMON->GetScore() + 1);
			GAMESOUND->play(SOUND_CHECKPOINT_PATH);
			timeStartCount = GetTickCount();
		}
	}
	else {
		if (GetTickCount() - timeStartPrepareChangeScene >= timeDuringPrepareChangeScene) {
			GAMESTATE->IsGameWin = true;
		}
	}


	SetHP(SIMON->GetHP());
	SetSP(SIMON->GetSP());
	SetLifeNumber(SIMON->GetLifeNumber());
	SetScore(SIMON->GetScore());
	SetWeaponLevel(SIMON->GetWeaponLevel());
	SetSubWeaponTag(SIMON->GetSubWeaponTag());

	//strGameFiguresInfomation = "HP: " + std::to_string(GetHP()) + "\n" + "SP: " + std::to_string(GetSP()) + "\n" + "Money: " + std::to_string(GetScore()) + "\n" + "WeaponLevel: " + std::to_string(GetWeaponLevel()) + "\n" + "SubWeapon_TAG: " + std::to_string(GetSubWeaponTag()) + "\n";
	//strTestGame = "SIMON\n x: " + std::to_string(SIMON->x) + "\ny: " + std::to_string(SIMON->y) + "\nWEAPON\n x: " + std::to_string(SIMON->getWeapon()->x) + "\ny: " + std::to_string(SIMON->getWeapon()->y) + "\nWEAPON_TYPE " + std::to_string(SIMON->getWeapon()->type) + "\nWEAPON_State " + std::to_string(SIMON->getWeapon()->state);
	strGameFiguresInfomation = std::to_string(GetScore());
}

void CVisualFigures::Render()
{
	RenderVisualImage();
	//GRAPHICS->PrintText(strTxtBoard.c_str(), 17, 0, 6, TEXT_COLOR_DEFAULT);

	/*GRAPHICS->PrintText(std::to_string(timeCount).c_str(), 17, 343, 6, TEXT_COLOR_DEFAULT);
	GRAPHICS->PrintText(std::to_string(GetSP()).c_str(), 17, 421, 23, TEXT_COLOR_DEFAULT);
	GRAPHICS->PrintText(std::to_string(GetLifeNumber()).c_str(), 17, 421, 40, TEXT_COLOR_DEFAULT);
	GRAPHICS->PrintText(strGameFiguresInfomation.c_str(), 17, 120, 6, TEXT_COLOR_DEFAULT);*/
	//GRAPHICS->PrintText(strTestGame.c_str(), 10, 5, 20, D3DCOLOR_XRGB(255, 255, 255));
	DrawNumber(timeCount, 343, 6);
	DrawNumber(GetSP(), 421, 23);
	DrawNumber(GetLifeNumber(), 421, 40);
	DrawNumber(GetScore(), 120, 6);
	DrawNumber(GetScore(), 120, 6);
	DrawNumber(GAMESTATE->stage->stageNumber, 505, 4);
}

void CVisualFigures::RenderVisualImage()
{
	SPRITES->Get(VISUALINFO_BACKGROUND_ID)->Draw(0, 0);

	if (GetSubWeaponTag() != OBJ_ITEM_SUBWEAPON_NULL) {
		SPRITES->Get(GetSubWeaponTag())->Draw(300, 28);
	}


	for (int i = 0; i < GetHP(); i++) {
		SPRITES->Get(ID_SPRITE_REDHP)->Draw(110 + 8 * i, 22);
	}
	for (int i = 0; i < GAMESTATE->gameBossHP; i++) {
		SPRITES->Get(ID_SPRITE_ORANGEHP)->Draw(110 + 8 * i, 42);
	}

}

CVisualFigures::CVisualFigures()
{
	/*strTxtBoard = "SCORE-0       TIME 0    STAGE 0  \n";
	strTxtBoard += "PLAYER                 =0\n";
	strTxtBoard += "ENEMY                P =0\n";*/
	strTxtBoard = TEXT_FIGURES_GAME;
	timeStartCount = GetTickCount();
}


CVisualFigures::~CVisualFigures()
{
}
