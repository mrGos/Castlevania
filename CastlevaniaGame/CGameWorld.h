#pragma once
#include "AppConfiguration.h"
#include <d3dx9.h>

#include "CTextures.h"
#include "CSprites.h"
#include "CAnimation.h"
#include "LoadResources.h"


#include "CKeyboard.h"
#include "CKeyGameHandler.h"

#include "CVisualFigures.h"
#include "CSceneManager.h"

#include "CGameState.h"
#include "CGround.h"
#include "Camera.h"

#include "CWeapon.h"
#include "CDagger.h"
#include "Static.h"
#include "CAxe.h"
#include "CHollyWater.h"
#include "CBoomerang.h"

#include "CGhost.h"
#include "CBat.h"
#include "CDog.h"
#include "CFishMan.h"
#include "CFireBall.h"

#include "CStair.h"
#include "CDoor.h"
#include "CVampireBat.h"

#include "CommonFunction.h"
#include "CScene_Level1.h"

class CGameWorld
{
private:

	static CGameWorld* _instance;

	CTextures * textures = TEXTURES;
	CSprites * sprites = SPRITES;
	CAnimations * animations = ANIMATIONS;

	//LoadResources loadHelper;
	LPCAMERA camera;
	/*LPGAMEOBJECTMANAGER objManager;*/

	/*CGraphics* graphics;
	CKeyboard* keyboard;
	CSceneManager* sceneManager;
	CVisualFigures* visual;*/
	//LPBACKGROUNDMAP bgmap;
public:

	static CGameWorld* getInstance();



	/*LPGAMEOBJECTMANAGER getObjManager();*/
	LPCAMERA getCamera() { return this->camera; }

	void Update(DWORD time = 0);
	void Render();
	~CGameWorld();
	CGameWorld();
};

