#include "CFireBall.h"
#include "CGameWorld.h"

CFireBall::CFireBall()
{

}
void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt);
	if (isObjectOutOfCameraView() || GetHP() <= 0)
		SetState(ObjectState::DIE);

	if (GAMESTATE->IsStopWatch)
		return;

	CGameObject::Update(dt);
	CGameObject::updateLocation();
}

void CFireBall::Render()
{
	SPRITES->Get(id)->Draw(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, isFlip);
	//RenderBoundingBox();
}

CFireBall::CFireBall(float x, float y, int direction)
{
	id = OBJ_ENEMY_FIREBALL;
	width = 17;
	height = 15;
	SetState(ObjectState::ALIVE);
	type = TeamType::ENEMY;

	SetHP(1);
	SetDamage(1);

	this->x = x;
	this->y = y;
	this->direction = direction;

	vx = direction * SIMON_WALKING_SPEED * 0.6;
}

CFireBall::~CFireBall()
{
}
