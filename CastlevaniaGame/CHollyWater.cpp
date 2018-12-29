#include "CHollyWater.h"
#include "CGameWorld.h"


void CHollyWater::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CHollyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += gy * dt;



	if (isFlame) {
		if (GetTickCount() - timeStartFlame >= timeDuringFlame) {
			SetState(ObjectState::DIE);
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != ObjectState::DIE)
		CalcPotentialCollisions(coObjects, coEvents);




	if (coEvents.size() == 0)
	{
		if (isObjectOutOfCameraView()) {
			CGameObject::SetState(ObjectState::DIE);
		}
		CGameObject::updateLocation();
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
				CWeapon::attackEnemy(e->obj);
				//}
				break;
			}
			case TeamType::STATIC:
			{
				if ((state == ObjectState::BURN) && (e->nx != 0 || e->ny != 0)) {

					e->obj->SetState(ObjectState::BURN);
					//SetState(ObjectState::DIE);
				}
				//CGameObject::updateLocation();

				break;
			}
			case TeamType::GROUND:
			{
				if ((GetState() != ObjectState::BURN) && (e->nx != 0 || e->ny != 0)) {
					GAMESOUND->play(SOUND_HOLLYWATER_PATH);
					SetState(ObjectState::BURN);
					timeStartFlame = GetTickCount();
					isFlame = true;
				}
				else {

					//y = e->obj->y - height;
				}

				break;
			}
			default:
				break;
			}

			if (!isFlame) {
				CGameObject::updateLocation();
			}

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CHollyWater::Render()
{
	if (GetState() == ObjectState::ALIVE) {
		water->Draw(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, isFlip);
	}
	else {
		animBurn->Render(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, isFlip);
	}
	//RenderBoundingBox();
}

CHollyWater::CHollyWater()
{
	id = OBJ_SUBWEAPON_HOLLYWATER;
	width = 40;
	/*height = 32;*/
	height = 25;
	SetState(ObjectState::ALIVE);
	SetDamage(SUBWEAPON_DAMAGE_DEFAULT);
	type = TeamType::WEAPON;
	x = 100;
	y = 275;
	gy = SIMON_GRAVITY;
	vx = SUBWEAPON_AXE_VELOCITY_X;
	vy = 0;

	water = SPRITES->Get(id);
	animBurn = ANIMATIONS->Get(Anim::ANIM_HOLLY_WATER_FLAME);
}


CHollyWater::~CHollyWater()
{
}
