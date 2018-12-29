#include "Static.h"
#include "EnumCommon.h"
#include "CGameWorld.h"
#include "CSceneManager.h"

void Static::SetItem(int itemId)
{
	this->itemId = itemId;
}

Static::Static()
{
	id = OBJ_STATIC_TORCH;
	type = TeamType::STATIC;
	CGameObject::SetState(ObjectState::ALIVE);
	vx = 0;
	vy = 0;
	//gy = SIMON_GRAVITY;
	if (id == OBJ_STATIC_TORCH)
		width = height = 12;
	else
	{
		width = 22;
		height = 45;
	}
}

void Static::generateItem()
{
	LPITEM item;
	(itemId != -1) ? item = new Item(itemId) : item = new Item();
	item->x = this->x /*+ width / 2*/;
	item->y = this->y;
	SCENEMANAGER->getGridManager()->AddObject(item);
}

void Static::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	switch (id)
	{
	case OBJ_STATIC_TORCH:
		right = x + 22;
		bottom = y + 45;
		break;
	case OBJ_STATIC_CANDLE:
		right = x + 12;
		bottom = y + 21;
	default:
		right = x + 12;
		bottom = y + 12;
		break;
	}
}

void Static::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetState() == ObjectState::BURN) {
		DWORD now = GetTickCount();
		if (now - timeStartBurn > timeDuringBurn)
		{
			generateItem();
			SetState(ObjectState::DIE);
		}
	}

	CGameObject::Update(dt);
	vy += gy * dt;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();



	// turn off collision when die 
	if (state != ObjectState::DIE)
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
			if (e->obj->type == TeamType::GROUND) {
				// block
				x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) {
					vy = 0;

				}
			}
			if (e->obj->type == TeamType::WEAPON) {

				//if (e->obj->nx != 0 || e->obj->ny != 0)
				SetState(ObjectState::BURN);
			}

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Static::Render()
{
	if (IsBreak) {
		ANIMATIONS->Get(Anim::ANIM_BURN_EFFECT)->Render(x + width / 2 - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255);
		return;
	}
	SPRITES->Get(id)->Draw(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255);
	//RenderBoundingBox();
}

void Static::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ObjectState::BURN:
		//SetState(ObjectState::DIE);
		if (!IsBreak) {
			timeStartBurn = GetTickCount();
			IsBreak = true;
		}
		break;
	case ObjectState::DIE:
		break;
	default:
		break;
	}
}

Static::~Static()
{
}
