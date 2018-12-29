#pragma once
#include"CGameObject.h"
#include <algorithm>
class CollisionManager
{
	static CollisionManager* instance;
public:
	static CollisionManager* getInstance();

	CDObject getBroadphaseBox(CGameObject& M);
	bool AABBCheck(CDObject& M, CDObject& S);
	float sweptAABB(CGameObject* M, CGameObject* S, int& normalX, int& normalY);
	void checkCollision(CGameObject* M, CGameObject* S);
	void preventMove(CGameObject* M, CGameObject* S);

	CollisionManager();
	~CollisionManager();
};

