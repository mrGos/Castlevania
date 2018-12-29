#include "CDagger.h"
#include "CGameWorld.h"


void CDagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != ObjectState::DIE)
		CalcPotentialCollisions(coObjects, coEvents);



	if (coEvents.size() == 0)
	{
		CGameObject::updateLocation();
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
			GAMESOUND->play(SOUND_HIT_PATH);
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

				break;
			}
			default:
				SetState(ObjectState::DIE);
				break;
			}

			CGameObject::updateLocation();

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CDagger::Render()
{
	SPRITES->Get(id)->Draw(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, isFlip);
	//RenderBoundingBox();
}

void CDagger::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case ObjectState::ALIVE:
		break;
	case ObjectState::DIE:
		x = 300;
		y = 200;

		break;
	default:
		break;
	}
}

CDagger::CDagger()
{
	id = OBJ_SUBWEAPON_DAGGER;
	width = 40;
	height = 22;
	SetState(ObjectState::ALIVE);
	SetDamage(SUBWEAPON_DAMAGE_DEFAULT);
	type = TeamType::WEAPON;
	x = 100;
	y = 275;
	vx = SIMON_WALKING_SPEED * 2.3;
	vy = 0;
}


CDagger::~CDagger()
{
}
