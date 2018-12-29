#include "CDog.h"
#include "CGameWorld.h"


CDog::CDog()
{

}

void CDog::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	UpdateState();
	CEnemy::Update(dt);

	if (GAMESTATE->IsStopWatch)
		return;


	float d = abs(x - SIMON->x);
	if (d > 10 && d < 100 && count == 0) {
		IsActivated = true;
		SetState(ObjectEnemy::OBJ_ENEMY_DOG_JUMP);
		count++;
		CGameObject::updateLocation();
		return;
	}


	if (!IsBreak  /*&& state != ObjectState::BURN*/) {
		if (count != 0) {
			CGameObject::Update(dt);
			vy += gy * dt;
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

			//x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			(ny > 0) ? y += min_ty * dy + ny * 0.4 : y += min_ty * dy + ny * 0.4f;

			if (ny != 0) {
				vy = 0;
				if (IsJumping && count != 0) {
					IsJumping = false;
					direction = -direction;
					SetState(ObjectEnemy::OBJ_ENEMY_DOG_RUN);
				}
			}


			//	// Collision logic with Goombas
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (e->obj->type != TeamType::GROUND) {
					/*if (e->ny < 0) {
					y += dy;
					}*/
					x += dx;
					if (IsJumping && count == 0) y += dy;
				}
				else if (e->obj->type == TeamType::GROUND) {

					//if (IsJumping && count != 0) {
					//	IsJumping = false;
					//	direction = -direction;
					//	SetState(ObjectEnemy::OBJ_ENEMY_DOG_RUN);
					//	//gy = 0;
					//}

					//if (nx != 0) vx = 0;
					if (ny != 0) {
						vy = 0;
					}


					x += dx;
					y -= min_ty * dy - ny * 0.4f;
				}

			}
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		animId = GetState();
	}
	//OutputDebugString(("\n" + std::to_string(GetState())).c_str());
}

void CDog::Render()
{
	if (IsBreak) {
		ANIMATIONS->Get(Anim::ANIM_BURN_EFFECT)->Render(x + width / 2 - GAMEWORLD->getCamera()->x, y + width / 2 - GAMEWORLD->getCamera()->y, 255);
		return;
	}
	ANIMATIONS->Get(animId)->Render(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, isFlip);
	//RenderBoundingBox();
}



void CDog::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ObjectEnemy::OBJ_ENEMY_DOG_IDLE:
		vx = 0;
		break;
	case ObjectEnemy::OBJ_ENEMY_DOG_JUMP:
		IsJumping = true;
		vx = direction * SUBWEAPON_AXE_VELOCITY_X*0.75;
		vy = -SUBWEAPON_AXE_VELOCITY_Y * 0.2;
		break;
	case ObjectEnemy::OBJ_ENEMY_DOG_RUN:
		vx = direction * ENEMY_GHOST_VELOCITY_X*2.5;
		break;
	default:
		break;
	}
}


CDog::CDog(float x, float y, int direction)
{
	id = ObjectEnemy::OBJ_ENEMY_DOG_IDLE;
	width = ENEMY_DOG_WIDTH;
	height = ENEMY_DOG_HEIGHT;
	SetState(ObjectEnemy::OBJ_ENEMY_DOG_IDLE);
	type = TeamType::ENEMY;

	SetHP(1);
	SetDamage(ENEMY_DAMAGE_DEFAULT);

	this->x = x;
	this->y = y;
	this->direction = direction;

	gy = SIMON_GRAVITY / 2;
	animId = ObjectEnemy::OBJ_ENEMY_DOG_IDLE;
}

CDog::~CDog()
{
}
