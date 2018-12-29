#include "Item.h"
#include "EnumCommon.h"
#include "CGameWorld.h"

Item::Item()
{
	CGameObject::SetState(ObjectState::ALIVE);
	type = TeamType::ITEM;
	RandomGenerateItem(true);
	init();
}

Item::Item(int itemID, float gravity)
{
	CGameObject::SetState(ObjectState::ALIVE);
	type = TeamType::ITEM;
	id = itemID;
	init();
	gy = gravity;
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	updateProperties();
	// Simple fall down
	/*vy += SIMON_GRAVITY * dt;*/
	vy += gy * dt;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (!IsEnableDisapear)
		if (GetTickCount() - timeStartDisappear > timeDuringDisappear) {
			SetState(ObjectState::DIE);
		}


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
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void Item::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case ObjectState::ALIVE:
		break;
	case ObjectState::DIE:
		x = 300;
		y = 0;

		break;
	default:
		break;
	}
}

void Item::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
	/*switch (id)
	{
	case OBJ_ITEM_SMALLHEART:
		right = x + 14;
		bottom = y + 12;
		break;
	case OBJ_ITEM_BIGHEART:
		right = x + 18;
		bottom = y + 15;
		break;
	case OBJ_ITEM_MONEYBAG:
		right = x + 23;
		bottom = y + 22;
		break;
	case OBJ_ITEM_MORNINGSTAR:
		right = x + 24;
		bottom = y + 24;
		break;
	case OBJ_ITEM_PORKCHOP:
		right = x + 24;
		bottom = y + 19;
		break;
	case OBJ_ITEM_MAGICCRYSTAL:
		right = x + 19;
		bottom = y + 22;
		break;
	case OBJ_ITEM_DAGGER:
		right = x + 24;
		bottom = y + 13;
		break;
	case OBJ_ITEM_AXE:
		right = x + 22;
		bottom = y + 21;
		break;
	case OBJ_ITEM_BOOMERANG:
		right = x + 22;
		bottom = y + 21;
		break;
	case OBJ_ITEM_FIREBOMB:
		right = x + 24;
		bottom = y + 24;
		break;
	default:
		right = x + 16;
		bottom = y + 16;
		break;
}*/

}

void Item::Render()
{
	SPRITES->Get(id)->Draw(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255);

}

void Item::updateProperties()
{
	switch (id)
	{
	case OBJ_ITEM_SMALLHEART:
		width = 14;
		height = 12;
		break;
	case OBJ_ITEM_BIGHEART:
		width = 18;
		height = 15;
		break;
	case OBJ_ITEM_MONEYBAG:
		width = 23;
		height = 22;
		break;
	case OBJ_ITEM_MORNINGSTAR:
		width = 24;
		height = 24;
		break;
	case OBJ_ITEM_PORKCHOP:
		width = 24;
		height = 19;
		break;
	case OBJ_ITEM_MAGICCRYSTAL:
		width = 19;
		height = 22;
		break;
	case OBJ_ITEM_DAGGER:
		width = 24;
		height = 13;
		break;
	case OBJ_ITEM_AXE:
		width = 22;
		height = 21;
		break;
	case OBJ_ITEM_BOOMERANG:
		width = 22;
		height = 21;
		break;
	case OBJ_ITEM_FIREBOMB:
		width = 24;
		height = 24;
		break;
	case OBJ_ITEM_STOPWATCH:
		width = 26;
		height = 23;
		break;
	case OBJ_ITEM_CROSS:
		width = 24;
		height = 24;
		break;
	default:
		width = 16;
		height = 16;
		break;
	}
}

void Item::GenerateFiguresItem(int id)
{
	switch (id)
	{
	case OBJ_ITEM_SMALLHEART:
		SetSP(1);
		break;
	case OBJ_ITEM_BIGHEART:
		SetSP(5);
		break;
	case OBJ_ITEM_MONEYBAG:
		SetScore(100);
		break;
	case OBJ_ITEM_MORNINGSTAR:
		SetWeaponLevel(GetWeaponLevel() + 1);
		break;
	case OBJ_ITEM_PORKCHOP:
		SetHP(8);
		break;
	case OBJ_ITEM_MAGICCRYSTAL:
		SetHP(SIMON_FULL_HP);
		break;
	case OBJ_ITEM_DAGGER:
		SetSubWeaponTag(OBJ_ITEM_DAGGER);
		break;
	case OBJ_ITEM_AXE:
		SetSubWeaponTag(OBJ_ITEM_AXE);
		break;
	case OBJ_ITEM_BOOMERANG:
		SetSubWeaponTag(OBJ_ITEM_BOOMERANG);
		break;
	case OBJ_ITEM_FIREBOMB:
		SetSubWeaponTag(OBJ_ITEM_FIREBOMB);
		break;
	case OBJ_ITEM_STOPWATCH:
		SetSubWeaponTag(OBJ_ITEM_STOPWATCH);
		break;
	default:
		break;
	}
}

void Item::RandomGenerateItem(bool isActive)
{
	if (!isActive)
	{
		id = OBJ_ITEM_BOOMERANG;
		return;
	}

	int RandomID = GetTickCount() % 11;
	switch (RandomID) {
	case 0:
		id = OBJ_ITEM_SMALLHEART;
		break;
	case 1:
		id = OBJ_ITEM_BIGHEART;
		break;
	case 2:
		id = OBJ_ITEM_MONEYBAG;
		break;
	case 3:
		id = OBJ_ITEM_MORNINGSTAR;
		break;
	case 4:
		id = OBJ_ITEM_DAGGER;
		break;
	case 5:
		id = OBJ_ITEM_AXE;
		break;
	case 6:
		id = OBJ_ITEM_BOOMERANG;
		break;
	case 7:
		id = OBJ_ITEM_FIREBOMB;
		break;
	case 8:
		id = OBJ_ITEM_PORKCHOP;
		break;
	case 9:
		id = OBJ_ITEM_STOPWATCH;
		break;
		/*case 10:
			id = OBJ_ITEM_CROSS;
			break;*/
	default:
		id = OBJ_ITEM_SMALLHEART;
		break;
	}
}

void Item::init()
{
	SetHP(0);
	SetSP(0);
	SetScore(0);
	SetWeaponLevel(0);
	SetSubWeaponTag(OBJ_ITEM_SUBWEAPON_NULL);

	GenerateFiguresItem(id);
	gy = ITEM_GRAVITY;
	x = 300;
	y = 0;

	timeStartDisappear = GetTickCount();
}

Item::~Item()
{
}

