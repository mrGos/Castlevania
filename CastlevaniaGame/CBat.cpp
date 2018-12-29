#include "CBat.h"
#include "CGameWorld.h"



void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt);
	UpdateState();

	if (GAMESTATE->IsStopWatch)
		return;

	if (!IsBreak) {
		vy += gy * dt;
		CGameObject::Update(dt);

		//x += dx;
		updateLocation();
	}


}

void CBat::Render()
{
	if (IsBreak) {
		ANIMATIONS->Get(Anim::ANIM_BURN_EFFECT)->Render(x + width / 2 - GAMEWORLD->getCamera()->x, y + width / 2 - GAMEWORLD->getCamera()->y, 255);
		return;
	}
	ANIMATIONS->Get(id)->Render(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, isFlip);
	//RenderBoundingBox();
}

void CBat::updateLocation()
{
	x += dx;
	y += flyYPos * directy;
	y += directy * dy / 10;
	if (y <= yFlyOffsetTop || y >= yFlyOffsetBottom)
		directy = -directy;
}

CBat::CBat(float x, float y, int direction)
{
	id = ObjectEnemy::OBJ_ENEMY_BAT_FLY;
	width = ENEMY_BAT_WIDTH;
	height = ENEMY_BAT_HEIGHT;
	SetState(ObjectState::ALIVE);
	type = TeamType::ENEMY;

	SetHP(1);
	SetDamage(1);

	this->x = x;
	this->y = y;
	yFlyOffsetBottom = this->y + 20;
	yFlyOffsetTop = this->y - 30;

	this->direction = direction;

	gy = 0;

	vx = direction * ENEMY_BAT_VELOCITY_X;
	vy = 0;
}


CBat::~CBat()
{
}
