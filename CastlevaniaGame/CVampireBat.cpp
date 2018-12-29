#include "CVampireBat.h"
#include "CGameWorld.h"

CGameState* gamestate;
Camera* camera;
CSimon* simon;
void CVampireBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//UpdateState();
	if (IsBreak) {
		if (GetTickCount() - timeStartBurn >= timeDuringBurn)
		{
			LPITEM itemMagicCrystial = new Item(OBJ_ITEM_MAGICCRYSTAL);
			itemMagicCrystial->SetPosition(x, y);
			itemMagicCrystial->IsEnableDisapear = true;
			SCENEMANAGER->getGridManager()->AddObject(itemMagicCrystial);
			SetState(ObjectState::DIE);
		}
	}

	/*if (this->isObjectOutOfCameraView())
	SetState(ObjectState::DIE);*/

	if (GetHP() <= 0 && !IsBreak) {
		timeStartBurn = GetTickCount();
		IsBreak = true;
		SetState(ObjectState::BURN);
	}

	gamestate->gameBossHP = GetHP();

	if (GAMESTATE->IsStopWatch)
		return;

	if (!IsActive)
		return;
	CGameObject::Update(dt);


	if (GetTickCount() - lastUntouchableTime > timeDuringUntouchable) {
		untouchableCount = 0;
		lastUntouchableTime = 0;
	}

	if (!IsBreak) {
		//intro update

		if (IsIntro) {
			if (GetTickCount() - timeStartIntro > timeDuringIntro) {
				if (activeCombat == 0) {
					IsIDLE = false;
					activeCombat++;
					GAMESOUND->stop(GAMESTATE->currentMusic);
					GAMESTATE->currentMusic = MUSIC_VAMPIREBAT_PATH;
					GAMESOUND->play(MUSIC_VAMPIREBAT_PATH, true);

				}
				if (prevDistance >= 10 && (x + width < rightArea)) {
					x += dx;
					y += dy;
					calculateDistance(x, posX_Intro, y, posY_Intro);
					prevDistance = prevDistance + (distance - prevDistance);
					//OutputDebugString(("distance: " + std::to_string(prevDistance) + "\n ").c_str());
				}
				else {
					IsIntro = false;
					//SetState(ObjectEnemy::OBJ_ENEMY_VAMPIREBAT_FLY);
					SetState(ObjectEnemy::OBJ_ENEMY_VAMPIREBAT_MOVETOSIDE);
				}
			}
		}

		/*CGameObject::Update(dt);*/

		//Moving Side
#pragma region MoveToSide
		if (IsMoveToSide) {
			if ((x + width >= rightArea)) {
				direction = Left;
				x += direction * dx;
				MoveToSideCount++;
			}
			else if (x <= leftArea)
			{
				direction = Right;
				x += direction * dx;
				MoveToSideCount++;
			}

			if (MoveToSideCount % 3 != 0) {
				x += direction * dx;
			}
			else {
				IsMoveToSide = false;
				MoveToSideCount = 1;
				SetState(ObjectEnemy::OBJ_ENEMY_VAMPIREBAT_FLY);
			}

		}
#pragma endregion



		//fly around
		//prevent two corner
		//fly Up Down around map
#pragma region Flying
		if (IsFlying) {
			if ((x + width > rightArea)) {
				direction = Left;
				x += direction * dx;
			}
			else if (x < leftArea)
			{
				direction = Right;
				x += direction * dx;
			}


			if (GetTickCount() - timeStartAttack > timeAttackHappen) {
				if (attackCount % 5 == 0) {
					timeAttackHappen = 8000;
				}
				else if (attackCount % 5 == 4) {
					IsFlying = false;
					MoveToSideCount = 1;
					attackCount++;
					OutputDebugString(("attackCount: " + std::to_string(attackCount) + "\n ").c_str());
					SetState(ObjectEnemy::OBJ_ENEMY_VAMPIREBAT_MOVETOSIDE);
					return;
				}
				if (timeAttackHappen - 2000 > 1500)
				{
					timeAttackHappen -= 2000;
				}
				OutputDebugString(("attackCount: " + std::to_string(attackCount) + "\n ").c_str());
				IsFlying = false;
				attackCount++;
				SetState(ObjectEnemy::OBJ_ENEMY_VAMPIREBAT_ATTACK);
			}

			x += direction * dx;

			if (y < yFlyingMiddle && yFlyingCount % 2 == 0) {
				y += dx;
			}
			else if (y >= yFlyingMiddle && yFlyingCount % 2 == 0) {
				yFlyingMiddle = posY_Intro;
				yFlyingCount++;
			}

			if (y > yFlyingMiddle && yFlyingCount % 2 == 1) {
				y -= dx;
			}
			else if (y <= yFlyingMiddle && yFlyingCount % 2 == 1) {
				yFlyingMiddle = 241.0f;
				yFlyingCount = 0;
			}

		}

#pragma endregion

		if (IsAttack) {

			if ((x + width + dx > rightArea)) {
				direction = Left;
				x = rightArea - width;
			}
			else if (x + dx < leftArea)
			{
				direction = Right;
				x = x;
			}
			else if (y + height > bottomArea || y < topArea) {

				updateDimension(x, posX_Intro, y, posY_Intro);
				prevDistance = distance;
				IsAttack = false;
				SetState(ObjectEnemy::OBJ_ENEMY_VAMPIREBAT_FLY);

			}
			//else if ((y + height > bottomArea)) {
			//	/*if (y > posX_Intro)
			//		y -= dy;*/
			//	y = bottomArea - height;
			//}
			//else if (y < topArea)
			//{
			//	/*if (y < posX_Intro)
			//		y += dy;*/
			//	y = topArea;
			//}

			if (prevDistance >= 20) {

				updateLocation(dt);
				//OutputDebugString(("distance: " + std::to_string(distance) + ", prevdistance: " + std::to_string(prevDistance) + "\n ").c_str());
			}
			else {
				IsAttack = false;
				SetState(ObjectEnemy::OBJ_ENEMY_VAMPIREBAT_FLY);
			}

		}
	}




	//OutputDebugString(("HP: " + std::to_string(GetHP()) + "\n ").c_str());
	//OutputDebugString(("x: " + std::to_string(x) + ", y: " + std::to_string(y) + "\n ").c_str());
	//OutputDebugString(("smx: " + std::to_string(xAttackPlayer) + ", smy: " + std::to_string(yAttackPlayer) + "\n ").c_str());
	/*OutputDebugString(("smx: " + std::to_string(SIMON->x) + ", smy: " + std::to_string(SIMON->y) + "\n ").c_str());*/
}

void CVampireBat::Render()
{
	if (IsBreak) {
		for (int i = 0; i < 3; i++) {
			ANIMATIONS->Get(Anim::ANIM_BURN_EFFECT)->Render(x + 20 * i - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255);
			ANIMATIONS->Get(Anim::ANIM_BURN_EFFECT)->Render(x + 20 * i - GAMEWORLD->getCamera()->x, y + 40 - GAMEWORLD->getCamera()->y, 255);
		}
		return;
	}

	if (IsIDLE)
		animIDLE->Render(x - camera->x, y - camera->y, 255);
	else
		animFly->Render(x - camera->x, y - camera->y, 255);

	//RenderBoundingBox();
}

void CVampireBat::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case ObjectEnemy::OBJ_ENEMY_VAMPIREBAT_IDLE:
		vx = 0.15f;
		vy = 0.15f;
		IsIDLE = true;
		updateDimension(x, posX_Intro, y, posY_Intro);
		prevDistance = distance;

		CGameObject::updateLocation();
		break;
	case ObjectEnemy::OBJ_ENEMY_VAMPIREBAT_FLY:
		vx = 0.1f;
		vy = 0.1f;
		IsFlying = true;
		timeStartAttack = GetTickCount();
		break;
	case ObjectEnemy::OBJ_ENEMY_VAMPIREBAT_MOVETOSIDE:
		IsMoveToSide = true;
		vx = 0.2f;
		vy = 0.2f;
		break;
	case ObjectEnemy::OBJ_ENEMY_VAMPIREBAT_ATTACK:
		vx = 0.3f;
		vy = 0.3f;
		(x - simon->x > 0) ? direction = Left : direction = Right;
		IsAttack = true;
		RetrievePlayerPosition(simon->x, simon->y);
		updateDimension(x, xAttackPlayer, y, yAttackPlayer);
		prevDistance = distance;
		//OutputDebugString(("xAttackPlayer: " + std::to_string(xAttackPlayer) + ", yAttackPlayer: " + std::to_string(yAttackPlayer) + "\n ").c_str());
		break;
	default:
		break;
	}
}

void CVampireBat::updateLocation(DWORD dt)
{
	//CGameObject::Update(dt);

	x += direction * dx;
	y += dy;
	calculateDistance(x, xAttackPlayer, y, yAttackPlayer);
	prevDistance = prevDistance + (distance - prevDistance);

}

void CVampireBat::startCombat()
{
	IsActive = true;
	IsIntro = true;
	timeStartIntro = GetTickCount();
	//SetState(ObjectEnemy::OBJ_ENEMY_BAT_FLY);
}

void CVampireBat::setArea(float l, float t, float r, float b)
{
	leftArea = l;
	rightArea = r;
	topArea = t;
	bottomArea = b;
}

CVampireBat::CVampireBat()
{
}

void CVampireBat::updateSquareEdge(float x1, float x2, float y1, float y2)
{
	sq1 = sqrt(pow(abs(y1 - y2), 2));
	sq2 = sqrt(pow(abs(x1 - x2), 2));
	//OutputDebugString(("sq1: " + std::to_string(sq1) + ", sq2: " + std::to_string(sq2) + "\n ").c_str());
}

void CVampireBat::calculateDistance(float x1, float x2, float y1, float y2)
{
	distance = abs(sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
	//OutputDebugString(("distance: " + std::to_string(distance) + "\n ").c_str());
}

void CVampireBat::calculateAngle(float squareEdge, float hypotenuse)
{
	try {
		angle = (squareEdge / hypotenuse) * 180 / PI;
		OutputDebugString(("angle: " + std::to_string(angle) + "\n ").c_str());
	}
	catch (exception  e) {
		angle = 0;
		OutputDebugString("Error divide 0");
	}

}

void CVampireBat::updateDimension(float x1, float x2, float y1, float y2)
{
	updateSquareEdge(x1, x2, y1, y2);
	calculateDistance(x1, x2, y1, y2);

	//calculateAngle(sq2, this->distance);


	/*vx = cos(angle)*vx;
	vy = sin(angle)*vy;*/
	vx *= sq2 / distance;
	vy *= sq1 / distance;




	//OutputDebugString(("dx: " + std::to_string(dx) + ", dy: " + std::to_string(dy) + "\n ").c_str());
}

void CVampireBat::RetrievePlayerPosition(float  posX, float posY)
{
	xAttackPlayer = posX;
	xBack = posX;
	yAttackPlayer = posY;
	yBack = posX_Intro;
}


CVampireBat::CVampireBat(float x, float y, int direction)
{
	id = ObjectEnemy::BOSS;

	this->x = x;
	this->y = y;
	width = ENEMY_VAMPIRE_BAT_WIDTH;
	height = ENEMY_VAMPIRE_BAT_HEIGHT;

	this->direction = direction;

	animIDLE = ANIMATIONS->Get(ObjectEnemy::OBJ_ENEMY_VAMPIREBAT_IDLE);
	animFly = ANIMATIONS->Get(ObjectEnemy::OBJ_ENEMY_VAMPIREBAT_ATTACK);

	SetState(ObjectEnemy::OBJ_ENEMY_VAMPIREBAT_IDLE);
	SetHP(SIMON_FULL_HP);
	SetDamage(BOSS_DAMAGE_DEFAULT);
	type = TeamType::ENEMY;

	gamestate = GAMESTATE;
	camera = CAMERA;
	simon = SIMON;
	timeDuringBurn = 1500;
}

CVampireBat::~CVampireBat()
{
}
