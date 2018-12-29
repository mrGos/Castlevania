#include "CollisionManager.h"


CollisionManager* CollisionManager::instance = 0;
CollisionManager* CollisionManager::getInstance()
{
	if (instance == 0)
		instance = new CollisionManager();
	return instance;
}

CDObject CollisionManager::getBroadphaseBox(CGameObject& M)
{
	float x, y, w, h;
	x = M.dx > 0 ? M.x : M.x + M.dx;
	y = M.dy > 0 ? M.y : M.y + M.dy;
	w = M.dx > 0 ? M.width + M.dx : M.width - M.dx;
	h = M.dy > 0 ? M.height + M.dy : M.height - M.dy;
	CDObject broadphasebox(x, y, w, h);

	return broadphasebox;
}

bool CollisionManager::AABBCheck(CDObject& M, CDObject& S)
{
	return (M.bottom() > S.top() && M.top() < S.bottom() && M.left() < S.right() && M.right() > S.left());
}

float CollisionManager::sweptAABB(CGameObject* M, CGameObject* S, int& normalx, int& normaly)
{
	normalx = 0;
	normaly = 0;
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	if (M->dx > 0.0f)
	{
		xInvEntry = S->x - (M->x + M->width);
		xInvExit = (S->x + S->width) - M->x;
	}
	else
	{
		xInvEntry = (S->x + S->width) - M->x;
		xInvExit = S->x - (M->x + M->width);
	}

	if (M->dy > 0.0f)
	{
		yInvEntry = S->y - (M->y + M->height);
		yInvExit = (S->y + S->height) - M->y;
	}
	else
	{
		yInvEntry = (S->y + S->height) - M->y;
		yInvExit = S->y - (M->y + M->height);
	}

	float xEntry, yEntry;
	float xExit, yExit;

	if (M->dx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / M->dx;
		xExit = xInvExit / M->dx;
	}

	if (M->dy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / M->dy;
		yExit = yInvExit / M->dy;
	}

	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	//	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	if (entryTime > exitTime || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else
	{
		//if (xEntry > yEntry)
		//{
		//	if (M->dx < 0.0f)
		//	{
		//		normalx = 1.0f;
		//		normaly = 0.0f;
		//	}
		//	else
		//	{
		//		normalx = -1.0f;
		//		normaly = 0.0f;
		//	}
		//}
		//else
		//{
		//	if (M->dy  < 0.0f)
		//	{
		//		normalx = 0.0f;
		//		normaly = 1.0f;
		//	}
		//	else
		//	{
		//		normalx = 0.0f;
		//		normaly = -1.0f;
		//	}
		//}
		if (M->left() < S->right() && M->right() > S->left())
		{
			if (M->dy > 0)
				normaly = -1;
			else
				normaly = 1;
			normalx = 0;
		}
		if (M->top() < S->bottom() && M->bottom() > S->top())
		{
			if (M->dx > 0)
				normalx = -1;
			else
				normalx = 1;
			normaly = 0;
		}

		return entryTime;
	}
}

void CollisionManager::checkCollision(CGameObject* M, CGameObject* S)
{
	/*if (!S->alive || !M->alive)
		return;

	M->dx -= S->dx;
	M->dy -= S->dy;

	RectF broadPhase = getBroadphaseBox(*M);
	if (AABBCheck(broadPhase, *S))
	{
		if (AABBCheck(*M, *S))
		{
			M->onAABBCheck(S);
			S->onAABBCheck(M);

			M->dx += S->dx;
			M->dy += S->dy;

			return;
		}
		int nx, ny;
		float sweptTime = sweptAABB(M, S, nx, ny);
		if (sweptTime < 1.0f)
		{
			M->onCollision(S, nx, ny);
			S->onCollision(M, nx, ny);
		}
	}

	M->dx += S->dx;
	M->dy += S->dy;*/
}

void CollisionManager::preventMove(CGameObject* M, CGameObject* S)
{
	//if (M->top() < S->bottom() && M->bottom() > S->top() && M->dx != 0)
	//{
	//	M->isCollision = true;
	//	if (M->dx > 0)
	//		M->dx = S->left() - M->right();
	//	else
	//		M->dx = S->right() - M->left();
	//	return;
	//}

	//if (M->left() < S->right() && M->right() > S->left() && M->dy != 0)
	//{
	//	M->isCollision = true;
	//	if (M->dy > 0)
	//		M->dy = S->top() - M->bottom();
	//	else
	//		M->dy = S->bottom() - M->top();
	//	return;
	//}

	//M->isCollisionCross = true;
}

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}