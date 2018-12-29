#include "CSimon.h"
#include "CGameWorld.h"
#include "EnumCommon.h"

CSimon* CSimon::_instance = 0;
CSimon::CSimon()
{
	Init();
	sceneManager = SCENEMANAGER;
}

void CSimon::Init()
{
	id = OBJ_ID::OBJ_SIMON;
	SetHP(SIMON_FULL_HP);
	SetSP(10);
	SetScore(0);
	SetLifeNumber(1);
	SetWeaponLevel(SIMON_FULL_WEAPONLEVEL);
	//SetSubWeaponTag(OBJ_ITEM_SUBWEAPON_NULL);
	SetSubWeaponTag(OBJ_ITEM_BOOMERANG);

	type = TeamType::LEAGUE;
	attackType = AttackType::HOLD;
	direction = Right;
	isFlip = true;
	IsRunning = true;
	SetState(SIMON_STATE::IDLE);
	nx = 1;
	x = 200;
	y = 100;
	width = 32;
	height = 60;
	gy = SIMON_GRAVITY;
	IsLock = false;
	IsWalkingCastle = false;
	IsEnter = false;
	//weapon
	_weapon = CWhip::getInstance();
}

void CSimon::SetAnimID()
{
	animId = state;
	if ((IsDown && !IsStairing) || (IsJumping && !IsStairing))  animId = JUMP;
	if (IsStairing) {
		if (vx == 0 && vy == 0 && !IsAttack) {
			if (typeStairing == ObjectSpecial::STAIRDOWN_LTR || typeStairing == ObjectSpecial::STAIRDOWN_RTL)
				animId = ID_ANIM_SIMON_DOWNSTAIR;
			else if ((typeStairing == ObjectSpecial::STAIRUP_LTR || typeStairing == ObjectSpecial::STAIRUP_RTL))
				animId = ID_ANIM_SIMON_UPSTAIR;
		}
	}
	if (IsAttack)
	{
		if (IsJumping)
		{
			animId = JUMP_ATTACK;
		}
		else if (IsDown)
		{
			if (!IsStairing) { animId = DOWN_ATTACK; }
		}
		else if (IsStairing)
		{
			(typeStairing == ObjectSpecial::STAIRUP_LTR || typeStairing == ObjectSpecial::STAIRUP_RTL) ? animId = STAIRUP_ATTACK : animId = JUMP_ATTACK;
		}
		else
			animId = ATTACK;
		isRepeatAnim = false;
	}
	else {
		isRepeatAnim = true;
	}

	if (IsWalkingCastle) animId = MOVE;
	if (IsEnter) animId = ENTER;
}

CSimon * CSimon::getInstance()
{
	if (_instance == 0)
		_instance = new CSimon();
	return _instance;
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt);
	DieHandle();

	/*if (!IsStairing)
		vy += gy * dt;*/

	if (IsLock) return;

	if (x + width + dx > GAMEWORLD->getCamera()->rightCornerBlock) { return; }
	if (x + dx < GAMEWORLD->getCamera()->leftCornerBlock) {
		x += 0.5f;
		return;
	}

	if (IsBossDefeated) {
		if (GetTickCount() - timeStartPrepareCheckpoint > timeDuringPrepareCheckpoint) {
			VISUALFIGURES->IsCheckPoint = true;
		}
	}

	if (IsStairing) {
		if (KEYBOARD->IsKeyDown(DIK_UP) && (typeStairing != ObjectSpecial::STAIR_STOP)) {

			if (typeStairing == ObjectSpecial::STAIRDOWN_RTL)
				typeStairing = ObjectSpecial::STAIRUP_LTR;
			else if (typeStairing == ObjectSpecial::STAIRDOWN_LTR)
				typeStairing = ObjectSpecial::STAIRUP_RTL;
			SetState(STAIRUP);
		}
		else if ((KEYBOARD->IsKeyDown(DIK_DOWN) && (typeStairing != ObjectSpecial::STAIR_STOP))) {


			if (typeStairing == ObjectSpecial::STAIRUP_RTL)
				typeStairing = ObjectSpecial::STAIRDOWN_LTR;
			else if (typeStairing == ObjectSpecial::STAIRUP_LTR)
				typeStairing = ObjectSpecial::STAIRDOWN_RTL;
			SetState(STAIRDOWN);
		}
		else {
			vx = 0;
			vy = 0;
		}
		CGameObject::Update(dt);
	}
	else
	{
		vy += gy * dt;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	//
	if (GetTickCount() - lastUntouchableTime > timeDuringUntouchable)
	{
		lastUntouchableTime = 0;
		untouchableCount = 0;
	}
	//
	if (GAMESTATE->IsStopWatch) {
		if (GetTickCount() - lastStopWatchTime > timeDuringStopWatch) {
			GAMESTATE->IsStopWatch = false;
			lastStopWatchTime = 0;
		}
	}

	if (GAMESTATE->IsCrossActivated) {
		if (GetTickCount() - lastCrossActivatedTime > timeDuringCrossActivated) {
			GAMESTATE->IsCrossActivated = false;
			GRAPHICS->SetColor(255, 255, 255);
			lastCrossActivatedTime = 0;
		}
	}


	if (IsAttack /*&&_weapon->IsEnable*/)
	{
		if (_weapon->IsEnable) {
			if (IsJumping) {
				_weapon->curAnim = ANIMATIONS->Get(JUMP_ATTACK)->getCurrent();
			}
			else if (IsDown) {
				_weapon->curAnim = ANIMATIONS->Get(DOWN_ATTACK)->getCurrent();
			}
			else if (IsStairing) {
				((typeStairing == ObjectSpecial::STAIRUP_LTR || typeStairing == ObjectSpecial::STAIRUP_RTL)) ? _weapon->curAnim = ANIMATIONS->Get(STAIRUP_ATTACK)->getCurrent() : _weapon->curAnim = ANIMATIONS->Get(JUMP_ATTACK)->getCurrent();
			}
			else {
				_weapon->curAnim = ANIMATIONS->Get(ATTACK)->getCurrent();
			}

			if (_weapon->curAnim == 2) GAMESOUND->play(SOUND_WHIP_PATH);

			DWORD now = GetTickCount();
			if (now - lastAttackTime > timeDuringAttack)
			{
				ANIMATIONS->Get(ATTACK)->resetAnim();
				ANIMATIONS->Get(DOWN_ATTACK)->resetAnim();
				ANIMATIONS->Get(JUMP_ATTACK)->resetAnim();
				ANIMATIONS->Get(STAIRUP_ATTACK)->resetAnim();

				IsAttack = false;
				isRepeatAnim = true;
				SetState(IDLE);
				IsRunning = true;
				_weapon->IsEnable = false;
				_weapon->curAnim = 0;
				ANIMATIONS->Get(_weapon->id)->resetAnim();
				//SetWeaponPosition();
			}
		}
		else {
			DWORD now = GetTickCount();
			if (now - lastAttackTime > timeDuringAttack)
			{
				ANIMATIONS->Get(ATTACK)->resetAnim();
				ANIMATIONS->Get(DOWN_ATTACK)->resetAnim();
				ANIMATIONS->Get(JUMP_ATTACK)->resetAnim();
				ANIMATIONS->Get(STAIRUP_ATTACK)->resetAnim();

				IsAttack = false;
				isRepeatAnim = true;
				SetState(IDLE);
				IsRunning = true;
			}
		}
	}

	// turn off collision when die
	//if (state != SIMON_STATE::DIE)
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		//if (!IsStairing)
		CGameObject::updateLocation();
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		if (ny > 0) {
			y += min_ty * dy + ny * 0.02f;
		}
		else {
			y += min_ty * dy + ny * 0.4f;
		}

		if (nx != 0) vx = 0;
		if (ny != 0) {
			vy = 0;
			if (IsJumping) {
				IsJumping = false;
				if (!IsAttack)SetState(IDLE);
			}
		}

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			switch (e->obj->type) {
			case TeamType::ITEM:
			{
				LPITEM item = dynamic_cast<LPITEM>(e->obj);
				if (e->nx != 0 || e->ny != 0) {
					(item->GetSubWeaponTag() == OBJ_ITEM_SUBWEAPON_NULL) ? GAMESOUND->play(SOUND_COLLECTITEM_PATH) : GAMESOUND->play(SOUND_COLLECTWEAPON_PATH);

					if (item->id == OBJ_ITEM_CROSS)
					{
						GAMESTATE->IsCrossActivated = true;
						lastCrossActivatedTime = GetTickCount();
					}
					else if (item->id == OBJ_ITEM_MAGICCRYSTAL) {
						BossDefeatedHandle();
					}
					else
						RetrieveFiguresFromItem(item);

					item->SetState(ObjectState::DIE);
				}
				//CGameObject::updateLocation();
				break;
			}
			//case TeamType::STATIC:
			//{
			//	if (e->ny < 0) {
			//		y += dy;
			//	}
			//	x += dx;
			//	/*if (ny < 0) {
			//		y += dy / 7;
			//	}
			//	else if (ny > 0) {
			//		y += dy / 7;
			//	}
			//	x += dx;*/
			//	break;
			//}
			case TeamType::WEAPON:
			{
				if (e->obj->id == OBJ_SUBWEAPON_BOOMERANG) {
					e->obj->SetState(ObjectState::DIE);
				}
				break;
			}
			case TeamType::ENEMY:
			{

				LPENEMY enemy = dynamic_cast<LPENEMY>(e->obj);
				if (e->ny < 0) {
					y += dy;
				}
				else {
				}
				x += dx;

				if (GAMESTATE->IsStopWatch)
					return;
				if (untouchableCount == 0 && !enemy->IsBreak) {
					beDamaged(e->obj->GetDamage());
					lastUntouchableTime = GetTickCount();
					untouchableCount = 1;
				}
				break;
			}
			case TeamType::STAIR:
			{
				if (e->obj->id != ObjectSpecial::STAIR_STOP) {
					IsAbleStairing = true;

					if (e->obj->id == ObjectSpecial::STAIRUP_LTR) {
						xStairOffset = e->obj->x + e->obj->width / 5;
					}
					else if (e->obj->id == ObjectSpecial::STAIRUP_RTL) {
						xStairOffset = e->obj->x + e->obj->width - 32 - 8;
						//xStairOffset = e->obj->x + 13;
					}
					else if (e->obj->id == ObjectSpecial::STAIRDOWN_LTR) {
						xStairOffset = e->obj->x + e->obj->width - 5;
					}
					else if (e->obj->id == ObjectSpecial::STAIRDOWN_RTL) {
						xStairOffset = e->obj->x - 8 - 16;
					}
				}
				else if (e->obj->id == ObjectSpecial::STAIR_STOP) {
					if (e->ny > 0)
						y += dy + min_ty * dy + ny * 0.02f;
					else if (e->ny < 0)
						y += dy + min_ty * dy + ny * 0.4f;

					IsStairing = false;
					IsAbleStairing = false;
					SetState(IDLE);
					vy += (gy * dt) / 9;
					stopRun();
				}
				typeStairing = e->obj->id;
				x += dx / 2;
				break;
			}
			case TeamType::DOOR:
			{
				LPDOOR door = dynamic_cast<LPDOOR>(e->obj);
				if (door->GetState() == ObjectSpecial::DOOR_IDLE) {
					GAMESTATE->IsLockingKeyBoard = true;
					GAMESTATE->stage->RebornHandle();
					if (direction == Right) {
						door->xOffsetCameraAfterUpdate = (x - 50);
						door->xOffsetPlayerAfterUpdate = (x + door->xOffsetCameraAfterUpdate - GAMEWORLD->getCamera()->x);
					}
					else {
						door->xOffsetCameraAfterUpdate = (x + 50);
						door->xOffsetPlayerAfterUpdate = (x - GAMEWORLD->getCamera()->x + GAMEWORLD->getCamera()->width - door->xOffsetCameraAfterUpdate);
					}
					x -= dx;
					SetState(IDLE);
					GAMESOUND->play(SOUND_DOOR_PATH);
				}

				if (door->GetState() == ObjectSpecial::DOOR_IDLE) {
					door->SetState(ObjectSpecial::DOOR_OPEN_ACTIVE);
				}
				break;
			}
			//case TeamType::GROUND:
			//{
			//	// block
			//	x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			//	y += min_ty * dy + ny * 0.9f;

			//	if (nx != 0) vx = 0;
			//	if (ny != 0) {
			//		vy = 0;
			//		if (IsJumping) {
			//			IsJumping = false;
			//			SetState(IDLE);
			//		}
			//	}
			//	break;
			//}
			default:
				if (e->obj->type != TeamType::GROUND) {
					if (e->ny > 0)
						y += dy + min_ty * dy + ny * 0.02f;
					else if (e->ny < 0)
						y += dy + min_ty * dy + ny * 0.4f;
					if (e->ny < 0) {
						y += dy;
					}
					x += dx;
					return;
				}

				CGround* gr = dynamic_cast<CGround*>(e->obj);
				if (gr->IsStairFlag) {
					return;
				}

				if (IsStairing) {
					if (typeStairing == ObjectSpecial::STAIRUP_LTR) {
						x = e->obj->x - 16;
						y = e->obj->y - height;
					}
					else if (typeStairing == ObjectSpecial::STAIRUP_RTL) {
						x = e->obj->x;
						y = e->obj->y - height;
					}
					SetState(IDLE);
				}

				IsAbleStairing = false;
				IsStairing = false;
				typeStairing = ObjectSpecial::STAIR_STOP;

				break;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	SetAnimID();
	_weapon->updateLocation();

	/*if (IsAbleStairing) {
		OutputDebugString("IsAbleStairing: true \n ");
	}
	else {
		OutputDebugString("IsAbleStairing: false \n ");
	}*/
	//OutputDebugString(("x: " + std::to_string(x) + ", y: " + std::to_string(y) + "\n ").c_str());
	/*if (typeStairing != ObjectSpecial::STAIR_STOP&&IsStairing)
		OutputDebugString("staring ");*/
}

void CSimon::Render()
{
	int alpha = 255;

	if (untouchableCount && GetTickCount() % 3 == 0) alpha = 80;					//Flash effect
	ANIMATIONS->Get(animId)->Render(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, alpha, isFlip, isRepeatAnim);
	//sub->Render();
	//_weapon->Render();

	//RenderBoundingBox();
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE::MOVE:
		run();
		break;
	case SIMON_STATE::JUMP:
		jump();
	case SIMON_STATE::IDLE:
		stopRun();
		break;
	case SIMON_STATE::STAIRUP:
		stairUp();
		break;
	case SIMON_STATE::STAIRDOWN:
		stairDown();
		break;
	case SIMON_STATE::ATTACK:
		attack();
		break;
	case SIMON_STATE::DIE:
		vy = -SIMON_JUMP_SPEED_Y / 2;
		break;
	case SIMON_STATE::WALKING_CASTLE:
		walk();
		break;
	case SIMON_STATE::ENTER:
		stopRun();
		IsEnter = true;
		break;
	default:
		break;
	}
}

void CSimon::run()
{
	if (IsDown) return;

	//IsRunning = true;
	if (IsRunning) {
		if (direction == DIRECTION::Left) {
			vx = -SIMON_WALKING_SPEED;
			nx = -1;
		}
		else {
			vx = SIMON_WALKING_SPEED;
			nx = 1;
		}
	}
}
void CSimon::jump() {
	if (!IsJumping)
	{
		IsJumping = true;
		vy = -SIMON_JUMP_SPEED_Y;
		//(nx > 0) ? vx = SIMON_WALKING_SPEED : vx = -SIMON_WALKING_SPEED;
	}
}
void CSimon::stopRun() {
	vx = 0;
}

void CSimon::attack()
{
	//playsound

	//
	stopRun();
	if (!IsAttack && !IsRunning && !_weapon->IsEnable && !IsAttack) {
		if (attackType == AttackType::THROW) {
			SetSP(GetSP() - 1);
			GenerateSubWeaponThrow();
		}
		else {
			_weapon->IsEnable = true;
			//_weapon->updateLocation();
		}

		lastAttackTime = GetTickCount();
		IsAttack = true;
	}
}

void CSimon::stairUp()
{
	/*if (typeStairing == ObjectSpecial::STAIRUP_LTR) {
		direction = Right;
		nx = 1;
		isFlip = true;
	}
	else if (typeStairing == ObjectSpecial::STAIRUP_RTL) {
		direction = Left;
		nx = -1;
		isFlip = false;
	}*/
	vy = -SIMON_JUMP_SPEED_Y * 0.15;
	if (typeStairing == ObjectSpecial::STAIRUP_LTR) {
		vx = -vy;
		direction = Right;
		nx = 1;
		isFlip = true;
	}
	else {
		vx = +vy;
		direction = Left;
		nx = -1;
		isFlip = false;
	}
}

void CSimon::stairDown()
{
	vy = SIMON_JUMP_SPEED_Y * 0.2;
	if (typeStairing == ObjectSpecial::STAIRDOWN_LTR) {
		vx = vy;
		direction = Right;
		nx = 1;
		isFlip = true;
	}
	else if (typeStairing == ObjectSpecial::STAIRDOWN_RTL) {
		vx = -vy;
		direction = Left;
		nx = -1;
		isFlip = false;
	}
}

void CSimon::walk()
{
	IsWalkingCastle = true;
	if (direction == DIRECTION::Left) {
		vx = -SIMON_WALKING_CASTLE_SPEED;
		nx = -1;
	}
	else {
		vx = SIMON_WALKING_CASTLE_SPEED;
		nx = 1;
	}
}

void CSimon::GenerateSubWeaponThrow()
{

	LPGAMEOBJECT subWeapon;

	switch (GetSubWeaponTag())
	{
	case OBJ_ITEM_DAGGER:
	{
		subWeapon = new CDagger();
		(direction == DIRECTION::Left) ? subWeapon->vx = -SUBWEAPON_DAGGER_VELOCITY_X : subWeapon->vx = SUBWEAPON_DAGGER_VELOCITY_X;
		GAMESOUND->play(SOUND_DAGGER_PATH);
		break;
	}
	case OBJ_ITEM_AXE:
	{
		subWeapon = new CAxe();
		(direction == DIRECTION::Left) ? subWeapon->vx = -SUBWEAPON_AXE_VELOCITY_X : subWeapon->vx = SUBWEAPON_AXE_VELOCITY_X;
		subWeapon->vy = -SUBWEAPON_AXE_VELOCITY_Y;
		GAMESOUND->play(SOUND_AXE_PATH);
		break;
	}
	case OBJ_ITEM_FIREBOMB:
	{
		subWeapon = new CHollyWater();
		(direction == DIRECTION::Left) ? subWeapon->vx = -SUBWEAPON_AXE_VELOCITY_X : subWeapon->vx = SUBWEAPON_AXE_VELOCITY_X;
		subWeapon->vy = -SUBWEAPON_AXE_VELOCITY_Y / 2;
		break;
	}
	case OBJ_ITEM_BOOMERANG:
	{
		subWeapon = new CBoomerang();
		(direction == DIRECTION::Left) ? subWeapon->vx = -SUBWEAPON_BOOMERANG_VELOCITY_X : subWeapon->vx = SUBWEAPON_BOOMERANG_VELOCITY_X;
		GAMESOUND->play(SOUND_BOOMERANG_PATH);
		break;
	}
	default:
		subWeapon = new CAxe();
		break;
	}

	subWeapon->y = y + height / 4;
	if (IsJumping || IsDown)subWeapon->y = y + SIMON_DOWN_BOX_HEIGHT / 2;
	if (direction == DIRECTION::Right) {
		subWeapon->isFlip = true;
		subWeapon->x = this->x + 10;
	}
	else {
		subWeapon->x = this->x - 10;
	}

	//SCENEMANAGER->getObjManager()->Add(subWeapon);
	sceneManager->getGridManager()->AddObject(subWeapon);
	_weapon->IsEnable = false;
}

void CSimon::DieHandle()
{
	if (GetHP() <= 0 || y > yDeathFlag) {
		if (GetState() != SIMON_STATE::DIE) {
			if (GetLifeNumber() > 0) {
				IsReborn = true;
				timeStartReborn = GetTickCount();
			}
			else {
				timeStartEndGame = GetTickCount();
			}
			GAMESOUND->stop(GAMESTATE->currentMusic);
			GAMESOUND->play(MUSIC_LOST_LIFENUMBER_PATH);
			GAMESTATE->IsLockingKeyBoard = true;
			VISUALFIGURES->IsStopTime = true;
			SetState(SIMON_STATE::DIE);
		}
		else {
			IsAttack = false;
			IsJumping = false;
			if (IsReborn) {
				//reborn
				if (GetTickCount() - timeStartReborn > timeDuringReborn) {
					IsReborn = false;
					SetHP(SIMON_FULL_HP);
					//SetState(IDLE);
					SetLifeNumber(GetLifeNumber() - 1);

					GAMESOUND->play(GAMESTATE->currentMusic);
					GAMESTATE->IsLockingKeyBoard = false;
					VISUALFIGURES->IsStopTime = false;
					VISUALFIGURES->timeCount = 300;

					if (IsInBossArea) {
						SIMON->SetPosition(CAMERA->x + 100, 200);
						SetState(IDLE);
						IsRunning = true;
						return;
					}

					SetPosition(GAMESTATE->stage->xReborn, GAMESTATE->stage->yReborn);
					CAMERA->SetPosition(GAMESTATE->stage->xReborn - CAMERA->width / 2, 0);
					if (CAMERA->x < 0) CAMERA->x = 0;

					if (GAMESTATE->stage->stageNumber < 3) {
						CScene_Level1* tempScene = dynamic_cast<CScene_Level1*>(SCENEMANAGER->curScene);
						tempScene->FlagAboveBasement = true;
						tempScene->FlagDownBasement = false;
					}
				}
			}
			else {
				//prepare end game
				if (prepareEndGameCount == 0) {
					timeStartEndGame = GetTickCount();
					IsPrepareEndGame = true;
					prepareEndGameCount++;
				}
			}

			//end game
			if (IsPrepareEndGame) {
				if (GetTickCount() - timeStartEndGame > timeDuringEndGame) {
					GAMESTATE->IsGameEnd = true;
				}
			}

		}
	}
}

void CSimon::RetrieveFiguresFromItem(LPITEM item)
{
	SetSP(GetSP() + item->GetSP());
	SetScore(GetScore() + item->GetScore());

	//retrieve Weapon level
	if (weaponLevel < SIMON_FULL_WEAPONLEVEL)
		SetWeaponLevel(GetWeaponLevel() + item->GetWeaponLevel());

	// retrieve subweapon tag
	if (item->GetSubWeaponTag() != OBJ_ITEM_SUBWEAPON_NULL)
		SetSubWeaponTag(item->GetSubWeaponTag());

	// retrieve HP
	if ((GetHP() + item->GetHP()) > SIMON_FULL_HP)
		SetHP(SIMON_FULL_HP);
	else
		SetHP((GetHP() + item->GetHP()));
}
void CSimon::BossDefeatedHandle()
{
	if (!IsBossDefeated) {
		IsBossDefeated = !IsBossDefeated;
		SetState(IDLE);
		VISUALFIGURES->IsStopTime = true;
		VISUALFIGURES->timeDuringCount = 10;
		GAMESTATE->IsLockingKeyBoard = true;
		GAMESOUND->stop(GAMESTATE->currentMusic);
		GAMESOUND->play(MUSIC_BOSS_DEFEATED_PATH);
		timeStartPrepareCheckpoint = GetTickCount();
	}


}

void CSimon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
	/*right = x + 32;
	bottom = y + 60;*/

	if (IsDown) bottom -= SIMON_DOWN_BOX_HEIGHT;
	if (GetState() == SIMON_STATE::DIE) {
		right = x + 71;
		bottom = y + 29;
	}
	//if (IsAttack)bottom += 3;
}

CSimon::~CSimon()
{
	delete this;
	delete _weapon;
}