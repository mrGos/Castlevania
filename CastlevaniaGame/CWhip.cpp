#include "CWhip.h"
#include "CSimon.h"
#include "CGameWorld.h"


CWhip* CWhip::_instance = 0;
void CWhip::updateProperty()
{
	if (SIMON->GetWeaponLevel() == 1) {
		id = OBJ_WEAPON_WHIP1;
	}
	else if (SIMON->GetWeaponLevel() == 2) {
		id = OBJ_WEAPON_WHIP2;
	}
	else if (SIMON->GetWeaponLevel() == 3) {
		id = OBJ_WEAPON_WHIP3;
	}

	switch (id)
	{
	case OBJ_WEAPON_WHIP:
		width = 42;
		height = 14;
		break;
	case OBJ_WEAPON_WHIP1:
		width = 42;
		height = 10;
		break;
	case OBJ_WEAPON_WHIP2:
		width = 66;
		height = 10;
		break;
		//custom whip3
	case OBJ_WEAPON_WHIP3:
		width = 221;
		height = 14;
		break;
	}
}
CWhip * CWhip::getInstance()
{
	if (_instance == 0)
		_instance = new CWhip();
	return _instance;
}

void CWhip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

	left = x;
	top = y;

	if (curAnim != 2)
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
		return;
	}

	right = x + width;
	bottom = y + height;
}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	updateProperty();
	if (x + width < GAMEWORLD->getCamera()->leftCornerBlock) {
		return;
	}

	curAnim = ANIMATIONS->Get(SIMON->animId)->getCurrent();

	if (!SIMON->IsAttack) {
		curAnim = 0;
		return;
	}

	if (curAnim == 2) {
		IsAttack = true;
		//y = SIMON->y + 5;
		/*(SIMON->GetWeaponLevel() == 2) ? vx = SIMON->nx*1.0f : vx = SIMON->nx * 0.75f;*/
		//(SIMON->GetWeaponLevel() >= 2) ? vx = SIMON->nx*1.0f : vx = SIMON->nx * 0.8f;
		/*GAMESOUND->play(SOUND_WHIP_PATH);*/
	}
	else {
		IsAttack = false;
		vx = 0;
	}

	this->updateLocation();


	//CGameObject::Update(dt);
	/*if (SIMON->IsJumping) {

	}*/


	if (!IsEnable || !IsAttack) return;


	//if (!IsAttack) return;


	//attack handle section	
	for (int i = 0; i < coObjects->size(); i++)
	{
		//GAMESOUND->play(SOUND_WHIP_PATH);
		//updateLocation();
		if (AABBCheckORI(this, coObjects->at(i))/* && (coObjects->at(i)->type == TeamType::STATIC || coObjects->at(i)->type == TeamType::ENEMY)*/) {

			switch (coObjects->at(i)->type) {
			case TeamType::STATIC:
				coObjects->at(i)->SetState(ObjectState::BURN);
				break;
			case TeamType::ENEMY:
				GAMESOUND->play(SOUND_HIT_PATH);
				/*AttackEnemy(coObjects->at(i), GetDamage())*/;
				CWeapon::attackEnemy(coObjects->at(i));
				break;
			case TeamType::GROUND:
				CGround * brick = dynamic_cast<CGround*>(coObjects->at(i));
				if (brick->IsAbleBreak) {
					coObjects->at(i)->SetState(ObjectState::BURN);
					GAMESOUND->play(SOUND_BRICK_BROKEN_PATH);
				}
				break;
			}

		}

	}
	//updateLocation();


#pragma region attackHandleSection
	//	vector<LPCOLLISIONEVENT> coEvents;
	//	vector<LPCOLLISIONEVENT> coEventsResult;
	//
	//	coEvents.clear();
	//
	//
	//
	//	// turn off collision when die 
	//	if (state != ObjectState::DIE)
	//		CalcPotentialCollisions(coObjects, coEvents);
	//
	//
	//
	//	if (coEvents.size() == 0)
	//	{
	//		updateLocation();
	//	}
	//	else
	//	{
	//		float min_tx, min_ty, nx = 0, ny;
	//
	//		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	//
	//
	//		//	// Collision logic with Goombas
	//		for (UINT i = 0; i < coEventsResult.size(); i++)
	//		{
	//			LPCOLLISIONEVENT e = coEventsResult[i];
	//
	//			/*if (e->obj->type == TeamType::ENEMY) {
	//
	//			}*/
	//			if (e->obj->type == TeamType::STATIC) {
	//				if (e->nx != 0 || e->ny != 0) {
	//					e->obj->SetState(ObjectState::BURN);
	//				}
	//			}
	//			updateLocation();
	//
	//		}
	//	}
	//
	//	// clean up collision events
	//	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
#pragma endregion
}

void CWhip::Render()
{
	/*if (IsEnable && state != ObjectState::DIE) {
	ANIMATIONS->Get(id)->Render(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, SIMON->isFlip, false);
	RenderBoundingBox();
	}*/

	if (IsEnable && state != ObjectState::DIE) {
		//ANIMATIONS->Get(id)->Render(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, SIMON->isFlip, false);
		int smAnim = ANIMATIONS->Get(SIMON->animId)->getCurrent();
		switch (smAnim)
		{
		case 0:
		case 1:
			/*if (SIMON->direction == DIRECTION::Left) {
			SPRITES->Get(id + 1 + smAnim)->Draw(SIMON->x + SIMON->width - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, SIMON->isFlip);
			}
			else
			{
			SPRITES->Get(id + 1 + smAnim)->Draw(SIMON->x - 10 - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, SIMON->isFlip);
			}*/

			SPRITES->Get(id + 1 + smAnim)->Draw(PosXPrepare() - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, SIMON->isFlip);
			break;

		case 2:
			/*	if (SIMON->direction == DIRECTION::Left) {
			SPRITES->Get(id + 1 + smAnim)->Draw(SIMON->x - width + 10 - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, SIMON->isFlip);
			}
			else
			{
			SPRITES->Get(id + 1 + smAnim)->Draw(SIMON->x + SIMON->width - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, SIMON->isFlip);
			}*/
			SPRITES->Get(id + 1 + smAnim)->Draw(PosXAttack() - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, SIMON->isFlip);
			break;
		}
		//RenderBoundingBox();
	}
}


void CWhip::updateLocation()
{
	(SIMON->IsDown) ? this->y = (SIMON->y + 45 / 3.5) : this->y = (SIMON->y + 60 / 4.5);
	if (SIMON->IsJumping || SIMON->IsStairing)this->y = (SIMON->y + 10);


	if (IsAttack) {
		(SIMON->direction == Left) ? x = SIMON->x - width + 10 : x = SIMON->x + SIMON->width;
		/*if (SIMON->direction == Left)
		{
		(SIMON->GetWeaponLevel() >= 2) ? x = SIMON->x - width : x = SIMON->x - SIMON->width - 10;
		if (SIMON->GetWeaponLevel() == 3)  x = SIMON->x - width + 10;
		}
		else {
		x = SIMON->x + SIMON->width;
		}*/


	}
	else {
		if (SIMON->direction == DIRECTION::Left) {
			x = SIMON->x + SIMON->width;
		}
		else
		{
			x = SIMON->x - 10;
		}
	}
	/*if (x <= GAMEWORLD->getCamera()->leftCornerBlock)x = GAMEWORLD->getCamera()->leftCornerBlock;*/
}

float CWhip::PosXPrepare()
{
	if (SIMON->direction == DIRECTION::Left) {
		return SIMON->x + SIMON->width;
	}
	else
	{
		return SIMON->x - 10;
	}
}

float CWhip::PosXAttack()
{
	if (SIMON->direction == Left)
		return SIMON->x - width + 10;
	return SIMON->x + SIMON->width;
}







CWhip::CWhip()
{
	id = OBJ_WEAPON_WHIP3;
	//SIMON->SetWeaponLevel(3);

	damage = WHIP_DAMAGE;
	SetState(ObjectState::ALIVE);
	//gy = SIMON_GRAVITY;
	vx = 0;
	vy = 0;
	type = TeamType::WEAPON;

	width = x + 10;
	height = y + 14;
}


CWhip::~CWhip()
{
}
