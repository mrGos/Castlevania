#include <d3dx9.h>
#include <algorithm>
//#include "CTextures.h"
//#include "CGameObject.h"
//#include "CAnimation.h"
#include "CGameWorld.h"
#include "CGameObject.h"


CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;
}

void CGameObject::InitPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

bool CGameObject::isObjectOutOfCameraView()
{
	//if ((x - GAMEWORLD->getCamera()->x) > GAMEWORLD->getCamera()->width || (x - GAMEWORLD->getCamera()->x) < /*-50*/0
	//	|| (y - GAMEWORLD->getCamera()->y) > GAMEWORLD->getCamera()->height || (y - GAMEWORLD->getCamera()->y) < /*-50*/0
	//	)
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
	if (!AABBCheckMoving(this, GAMEWORLD->getCamera()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CGameObject::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}


/*
Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	SweptAABB(							//common function
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

//bool CGameObject::AABBCheckRE(LPGAMEOBJECT M, LPGAMEOBJECT S)
//{
//	float ml = 0.0f, mt = 0.0f, mr = 0.0f, mb = 0.0f;
//	float sl = 0.0f, st = 0.0f, sr = 0.0f, sb = 0.0f;
//
//	M->GetBoundingBox(ml, mt, mr, mb);
//	S->GetBoundingBox(sl, st, sr, sb);
//
//	return (mb > st && mt < sb && ml <sr &&mr > sl);
//}

/*
Calculate potential collisions with the list of colliable objects

coObjects: the list of colliable objects
coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty,
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}




void CGameObject::AttackEnemy(CGameObject* & enemy, int damage)
{
	enemy->SetHP(enemy->GetHP() - damage);
}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = TEXTURES->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	GRAPHICS->Draw(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, false, bbox, rect.left, rect.top, rect.right, rect.bottom, 200);

}



void CGameObject::updateLocation()
{
	x += dx;
	y += dy;
}

CGameObject::~CGameObject()
{

}