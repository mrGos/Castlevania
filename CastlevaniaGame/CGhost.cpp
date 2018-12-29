#include "CGhost.h"
#include "CGameWorld.h"




void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt);
	UpdateState();

	float d = abs(x - SIMON->x);
	if (d > 10 && d < 200) IsActivated = true;

	if (!IsActivated || GAMESTATE->IsStopWatch) return;

	if (!IsBreak) {
		vy += gy * dt;
		CGameObject::Update(dt);
		/*x += dx;*/
	}


	/*if (isObjectOutOfCameraView()) SetState(ObjectState::DIE);
	if (GetHP() <= 0) SetState(ObjectState::BURN);

	(vx > 0) ? isFlip = true : isFlip = false;*/
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
			}
			else if (e->obj->type == TeamType::GROUND) {
				x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
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
}

void CGhost::Render()
{
	if (IsBreak) {
		ANIMATIONS->Get(Anim::ANIM_BURN_EFFECT)->Render(x + width / 2 - GAMEWORLD->getCamera()->x, y + width / 2 - GAMEWORLD->getCamera()->y, 255);
		return;
	}
	if (IsActivated)
		ANIMATIONS->Get(id)->Render(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, isFlip);
	//RenderBoundingBox();
}

CGhost::CGhost()
{
	id = OBJ_ENEMY_GHOST;
	width = ENEMY_GHOST_WIDTH;
	height = ENEMY_GHOST_HEIGHT;
	SetState(ObjectState::ALIVE);
	type = TeamType::ENEMY;

	SetHP(1);
	SetDamage(1);

	x = 100;
	y = 253;
	vx = direction * ENEMY_GHOST_VELOCITY_X;
	gy = SIMON_GRAVITY;
}


CGhost::CGhost(float x, float y, int direction)
{
	id = OBJ_ENEMY_GHOST;
	width = ENEMY_GHOST_WIDTH;
	height = ENEMY_GHOST_HEIGHT;
	SetState(ObjectState::ALIVE);
	type = TeamType::ENEMY;

	SetHP(1);
	SetDamage(ENEMY_DAMAGE_DEFAULT);

	this->x = x;
	this->y = y;
	this->direction = direction;

	vx = direction * ENEMY_GHOST_VELOCITY_X*0.4;
	vy = 0;
	gy = SIMON_GRAVITY / 2;
}

CGhost::~CGhost()
{
}
