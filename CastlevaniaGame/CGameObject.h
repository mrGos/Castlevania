#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "CAnimation.h"
#include "CGraphics.h"
#include "CDObject.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject : public CDObject
{
protected:
	int lifeNumber = 0;
	int hp, sp, weaponLevel, score, subWeaponTag;
	int damage = 0;
public:

	int type;

	int direction;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;

	int state;




	DWORD dt;

	vector<LPANIMATION> animations;

	bool isFlip = false;

public:
	void SetSize(int w, int h) { this->width = w, this->height = h; }
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	void SetHP(int hp) { this->hp = hp; };
	int  GetHP() { return this->hp; }
	void SetSP(int sp) { this->sp = sp; };
	int  GetSP() { return this->sp; }
	void SetWeaponLevel(int weaponLevel) { this->weaponLevel = weaponLevel; };
	int  GetWeaponLevel() { return this->weaponLevel; }
	void SetSubWeaponTag(int subWeaponTag) { this->subWeaponTag = subWeaponTag; };
	int  GetSubWeaponTag() { return this->subWeaponTag; }
	void SetDamage(int damage) { this->damage = damage; };
	int  GetDamage() { return this->damage; }
	void SetScore(int score) { this->score = score; };
	int  GetScore() { return this->score; }
	void SetLifeNumber(int lnum) { this->lifeNumber = lnum; };
	int  GetLifeNumber() { return this->lifeNumber; }

	void AttackEnemy(CGameObject* &enemy, int damage);

	int GetState() { return this->state; }


	void RenderBoundingBox();

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	//bool AABBCheckRE(LPGAMEOBJECT  M, LPGAMEOBJECT  S);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);



	CGameObject();
	void InitPosition(float x, float y);
	bool isObjectOutOfCameraView();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;																	//abstract
	virtual void SetState(int state) { this->state = state; }
	virtual void updateLocation();

	virtual ~CGameObject();
};

