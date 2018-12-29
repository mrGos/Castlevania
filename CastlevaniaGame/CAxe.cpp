#include "CAxe.h"
#include "CGameWorld.h"


void CAxe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += gy * dt;

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

					e->obj->SetState(ObjectState::BURN);
					SetState(ObjectState::DIE);
				}
				//CGameObject::updateLocation();
				GAMESOUND->play(SOUND_HIT_PATH);
				break;
			}
			case TeamType::LEAGUE:
			{
				if (e->nx != 0 || e->ny != 0) {
					SetState(ObjectState::DIE);
				}
				y -= 10;
				break;
			}

			}
			updateLocation();
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CAxe::Render()
{
	ANIMATIONS->Get(id)->Render(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, isFlip);
}


void CAxe::updateLocation()
{
	x += dx;
	y += dy;
}

CAxe::CAxe()
{
	id = OBJ_SUBWEAPON_AXE;
	x = 100;
	y = 100;
	SetDamage(SUBWEAPON_DAMAGE_DEFAULT);
	width = SUBWEAPON_AXE_WIDTH;
	height = SUBWEAPON_AXE_HEIGHT;
	gy = SIMON_GRAVITY;
	vy = 0;
	vx = 0;
}


CAxe::~CAxe()
{
}
