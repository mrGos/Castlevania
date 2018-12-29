#include "CKeyGameHandler.h"
#include "EnumCommon.h"
#include "CGameWorld.h"


CKeyboard* keyboard;
//CSimon* player;
CKeyGameHandler::CKeyGameHandler()
{
	//gamestate = GAMESTATE;
	keyboard = KEYBOARD;
	//player = SIMON;
}

void CKeyGameHandler::KeyState(BYTE * state)
{
	if (GAMESTATE->IsLockingKeyBoard == true) return;

	if (keyboard->IsKeyDown(DIK_RIGHT) && !SIMON->IsStairing) {
		SIMON->direction = Right;
		SIMON->isFlip = true;
		SIMON->SetState(SIMON_STATE::MOVE);
	}
	//	SIMON->SetState(SIMON_STATE::MOVE_RIGHT);
	else if (keyboard->IsKeyDown(DIK_LEFT) && !SIMON->IsStairing) {
		SIMON->direction = Left;
		SIMON->isFlip = false;
		SIMON->SetState(SIMON_STATE::MOVE);
	}
	else if (keyboard->IsKeyDown(DIK_UP) && SIMON->IsStairing) {

	}

}


void CKeyGameHandler::OnKeyDown(int KeyCode)
{
	if (GAMESTATE->IsLockingKeyBoard == true) return;
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
#pragma region TagSubweapon
	case DIK_1:
		SIMON->SetSubWeaponTag(OBJ_ITEM_BOOMERANG);
		break;
	case DIK_2:
		SIMON->SetSubWeaponTag(OBJ_ITEM_AXE);
		break;
	case DIK_3:
		SIMON->SetSubWeaponTag(OBJ_ITEM_FIREBOMB);
		break;
	case DIK_4:
		SIMON->SetSubWeaponTag(OBJ_ITEM_DAGGER);
		break;
	case DIK_5:
		SIMON->SetSubWeaponTag(OBJ_ITEM_STOPWATCH);
		break;
#pragma endregion
		/*case DIK_R:
			SIMON->SetHP(0);
			break;*/
	case DIK_UP:
	{
		if (SIMON->IsAbleStairing && !SIMON->IsDown && !SIMON->IsJumping && (SIMON->typeStairing != ObjectSpecial::STAIR_STOP && SIMON->typeStairing != ObjectSpecial::STAIRDOWN_LTR && SIMON->typeStairing != ObjectSpecial::STAIRDOWN_RTL)) {

			SIMON->SetState(STAIRUP);
			SIMON->IsStairing = true;
			SIMON->IsAbleStairing = false;
			SIMON->x = SIMON->xStairOffset;

			if (SIMON->typeStairing == ObjectSpecial::STAIRUP_LTR) {
				SIMON->SetPosition(SIMON->x + 5, SIMON->y - 5);
			}
			else if (SIMON->typeStairing == ObjectSpecial::STAIRUP_RTL) {
				SIMON->SetPosition(SIMON->x - 15, SIMON->y - 15);
			}
		}

		break;
	}
	case DIK_DOWN:
		if (SIMON->IsAbleStairing && !SIMON->IsDown && !SIMON->IsJumping && (SIMON->typeStairing != ObjectSpecial::STAIR_STOP && SIMON->typeStairing != ObjectSpecial::STAIRUP_LTR && SIMON->typeStairing != ObjectSpecial::STAIRUP_RTL)) {
			SIMON->SetState(STAIRDOWN);
			SIMON->IsStairing = true;
			SIMON->IsAbleStairing = false;
			SIMON->x = SIMON->xStairOffset;

			if (SIMON->typeStairing == ObjectSpecial::STAIRDOWN_LTR) {
				SIMON->SetPosition(SIMON->x + 5, SIMON->y + 5);
				/*SIMON->x += 5;
				SIMON->y += 5;*/
			}
			else if (SIMON->typeStairing == ObjectSpecial::STAIRDOWN_RTL) {
				SIMON->SetPosition(SIMON->x - 5, SIMON->y + 5);
			}
		}

		if (!SIMON->IsAttack && !SIMON->IsJumping && !SIMON->IsStairing) {
			SIMON->IsDown = true;
			SIMON->stopRun();
		}

		break;
	case DIK_Z:
		if (!SIMON->IsAttack && !SIMON->getWeapon()->IsEnable/* && !SIMON->IsStairing*/) {
			SIMON->attackType = AttackType::HOLD;
			SIMON->IsRunning = false;
			SIMON->SetState(ATTACK);
		}
		break;
	case DIK_X:
		if (SIMON->GetSubWeaponTag() == OBJ_ITEM_STOPWATCH) {
			if (!GAMESTATE->IsStopWatch) {
				SIMON->SetSP(SIMON->GetSP() - 5);
				GAMESTATE->IsStopWatch = true;
				SIMON->lastStopWatchTime = GetTickCount();
			}
		}
		else if (!SIMON->IsAttack && !SIMON->getWeapon()->IsEnable && SIMON->GetSP() > 0) {
			SIMON->attackType = AttackType::THROW;
			SIMON->IsRunning = false;
			SIMON->SetState(ATTACK);
		}
		break;
	case DIK_SPACE:
		if (!SIMON->IsAttack && !SIMON->IsStairing) {
			SIMON->SetState(SIMON_STATE::JUMP);
		}
		break;
		//case DIK_A: // reset
		//	/*SIMON->x = 100;
		//	SIMON->y = 100;*/

		//	SIMON->x = /*3392*/5220;
		//	SIMON->y = 100;
		//	GAMEWORLD->getCamera()->x = 5220 - GAMEWORLD->getCamera()->width / 2;
		//	GAMEWORLD->getCamera()->y = 0;

		//	SIMON->getWeapon()->x = 100;
		//	SIMON->getWeapon()->y = 100;
		//	SIMON->SetHP(16);

		break;
	case DIK_RETURN: // reset
		if (GAMESTATE->IsStartGame == false) GAMESTATE->IsStartGame = true;
		break;
	default:
		break;
	}
}

void CKeyGameHandler::OnKeyUp(int KeyCode)
{
	if (GAMESTATE->IsLockingKeyBoard == true) return;

	switch (KeyCode)
	{
	case DIK_DOWN:
		if (!SIMON->IsStairing&&SIMON->state != STAIRUP && SIMON->state != STAIRDOWN) {
			SIMON->IsDown = false;
			SIMON->y -= SIMON_DOWN_BOX_HEIGHT;
			SIMON->SetState(IDLE);
		}
		break;
	case DIK_LEFT:
		if (!SIMON->IsStairing) {
			SIMON->SetState(IDLE);
		}
		break;
	case DIK_RIGHT:
		if (!SIMON->IsStairing) {
			SIMON->SetState(IDLE);
		}
		break;
	default:
		break;
	}
}

CKeyGameHandler::~CKeyGameHandler()
{
}
