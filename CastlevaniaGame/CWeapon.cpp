#include "CWeapon.h"
#include "CGameWorld.h"


void CWeapon::attackEnemy(LPGAMEOBJECT &enemyObj)
{
	//GAMESOUND->play(SOUND_HIT_PATH);
	if (enemyObj->id == ObjectEnemy::BOSS) {
		LPENEMY enemy = dynamic_cast<LPENEMY>(enemyObj);
		if (enemy->untouchableCount == 0) {
			enemy->untouchableCount += 1;
			enemy->lastUntouchableTime = GetTickCount();
			AttackEnemy(enemyObj, GetDamage());
			OutputDebugString(("attackBoss: "));
		}
	}
	else {
		AttackEnemy(enemyObj, GetDamage());
	}

}

CWeapon::CWeapon()
{
}


CWeapon::~CWeapon()
{
}
