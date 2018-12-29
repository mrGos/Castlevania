#include "CFishMan.h"
#include "CGameWorld.h"
#include "CSceneManager.h"

CFishMan::CFishMan()
{
}

void CFishMan::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt);
	UpdateState();
	if (GAMESTATE->IsStopWatch)
		return;

	float d = abs(x - SIMON->x);
	if (d > 10 && d < 100) {
		IsVisible = true;
	}
	if (!IsVisible) return;

	if (!IsBreak /*&& state != ObjectState::BURN*/) {
		vy += gy * dt;
		CGameObject::Update(dt);
		//}


		//if (GetState() == ObjectState::BURN)
		//	SetState(GetState() == ObjectState::DIE);

		if (IsJumping) {
			if (count != 0) {
				IsJumping = false;
				//direction = -direction;
				//SetState(ObjectEnemy::OBJ_ENEMY_FISHMAN_RUN);
				//gy = 0;
			}
			else {
				if (y <= yOffsetStopJump)
					count++;
				else {
					CGameObject::updateLocation();
				}
			}
			return;
		}

		if (IsRunning) {
			if (GetTickCount() - timeStartRuning > timeDuringRuning) {
				SetState(ObjectEnemy::OBJ_ENEMY_FISHMAN_ATTACK);
				timeDuringRuning += 300;
				IsRunning = false;
			}
		}

		if (IsAttack) {
			if (GetTickCount() - timeStartAttack > timeDuringAttack) {
				OutputDebugString(("fishman state: " + std::to_string(GetState()) + "\n ").c_str());
				direction = -direction;
				SetState(ObjectEnemy::OBJ_ENEMY_FISHMAN_RUN);
				IsAttack = false;
			}
		}

	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != ObjectState::DIE || state != ObjectState::BURN)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		CGameObject::updateLocation();
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);


		//	// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->type != TeamType::GROUND) {
				x += dx;
				if (IsJumping) y += dy;
			}
			else if (e->obj->type == TeamType::GROUND) {
				if (count == 1) {
					SetState(ObjectEnemy::OBJ_ENEMY_FISHMAN_RUN);
					count++;
				}

				x += min_tx * dx + nx * 0.4f;
				(ny > 0) ? y += min_ty * dy + ny * 0.02f : y += min_ty * dy + ny * 0.4f;


				//if (nx != 0) vx = 0;
				if (ny != 0) {
					vy = 0;
				}


				x += dx;
			}
			break;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	animId = GetState();
	/*if (this->isObjectOutOfCameraView())
		SetState(ObjectState::DIE);*/
}

void CFishMan::Render()
{
	if (IsVisible && GetState() != ObjectState::DIE) {
		if (IsBreak) {
			ANIMATIONS->Get(Anim::ANIM_BURN_EFFECT)->Render(x + width / 2 - GAMEWORLD->getCamera()->x, y + width / 2 - GAMEWORLD->getCamera()->y, 255);
			return;
		}
		ANIMATIONS->Get(animId)->Render(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, isFlip);
		//RenderBoundingBox();
	}
}

void CFishMan::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ObjectEnemy::OBJ_ENEMY_FISHMAN_ATTACK:
	{
		vx = 0;
		IsAttack = true;
		timeStartAttack = GetTickCount();
		//fireball attack
		//LPGAMEOBJECT fireball = new CFireBall((direction == Right) ? x + width : x, y + 2, direction);
		LPGAMEOBJECT fireball = new CFireBall((direction == Right) ? x + width : x, y + height / 4, direction);
		//SCENEMANAGER->getObjManager()->Add(fireball);
		SCENEMANAGER->getGridManager()->AddObject(fireball);
		//-----//
		break;
	}
	case ObjectEnemy::OBJ_ENEMY_FISHMAN_JUMP:
		IsJumping = true;
		vy = -ENEMY_FISHMAN_VELOCITY_Y * 1.2;
		break;
	case ObjectEnemy::OBJ_ENEMY_FISHMAN_RUN:
		IsRunning = true;
		timeStartRuning = GetTickCount();
		vx = direction * ENEMY_FISHMAN_VELOCITY_X*0.6;
		break;
	default:
		break;
	}
}


CFishMan::CFishMan(float x, float y, int direction)
{
	id = ObjectEnemy::OBJ_ENEMY_FISHMAN_JUMP;
	width = ENEMY_FISHMAN_WIDTH;
	/*height = 69;*/
	height = ENEMY_FISHMAN_HEIGHT;
	SetState(ObjectEnemy::OBJ_ENEMY_FISHMAN_JUMP);
	type = TeamType::ENEMY;

	SetHP(1);
	SetDamage(1);

	this->x = x;
	this->y = y;
	this->direction = direction;

	gy = ENEMY_FISHMAN_GRAVITY;
	animId = ObjectEnemy::OBJ_ENEMY_FISHMAN_JUMP;
}

CFishMan::~CFishMan()
{
}
