#include "CBoomerang.h"
#include "CGameWorld.h"


void CBoomerang::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);



	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != ObjectState::DIE)
		CalcPotentialCollisions(coObjects, coEvents);



	if (coEvents.size() == 0)
	{
		updateLocation();
		if (isObjectOutOfCameraView()) {
			CGameObject::SetState(ObjectState::DIE);
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);


		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			switch (e->obj->type) {
			case TeamType::ENEMY:
			{
				/*if (e->nx != 0 || e->ny != 0) {*/
				GAMESOUND->play(SOUND_HIT_PATH);
				CWeapon::attackEnemy(e->obj);
				//}
				break;
			}
			case TeamType::STATIC:
			{
				if (e->nx != 0 || e->ny != 0) {
					GAMESOUND->play(SOUND_HIT_PATH);
					e->obj->SetState(ObjectState::BURN);
					//SetState(ObjectState::DIE);
				}
				//CGameObject::updateLocation();

				break;
			}
			case TeamType::LEAGUE:
			{
				SetState(ObjectState::DIE);
				break;
			}

			}

			updateLocation();

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBoomerang::Render()
{
	ANIMATIONS->Get(id)->Render(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, isFlip);
	//RenderBoundingBox();
}

void CBoomerang::updateLocation()
{
	x += dx;
	bool checkTurnBack = (!IsTurnBack && vx > 0 && (x + dx >= GAMEWORLD->getCamera()->x + GAMEWORLD->getCamera()->width - 15) || !IsTurnBack && vx < 0 && (x + dx <= GAMEWORLD->getCamera()->x + 15)) ? true : false;
	if (checkTurnBack)
	{
		vx = -vx * 0.6;
		IsTurnBack = !IsTurnBack;
	}
}
CBoomerang::CBoomerang()
{
	id = OBJ_SUBWEAPON_BOOMERANG;
	width = 35;
	height = 31;
	SetState(ObjectState::ALIVE);
	SetDamage(SUBWEAPON_DAMAGE_DEFAULT);
	type = TeamType::WEAPON;
	x = 100;
	y = 275;
	vx = SIMON_WALKING_SPEED * 2.3;
	vy = 0;

}


CBoomerang::~CBoomerang()
{
}
