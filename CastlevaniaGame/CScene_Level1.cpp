#include "CScene_Level1.h"
#include "CGameWorld.h"
#include "CSceneManager.h"

void CScene_Level1::init()
{
	bgmap = new BackgroundMap();
	bgmap->InitMap(LEVEL1_TILE_BACKGROUNDMAP_FILEPATH, 10000);

	/*GAMESTATE->currentMusic = MUSIC_LEVEL1_PATH;
	GAMESOUND->play(GAMESTATE->currentMusic, true);*/

	SIMON->yDeathFlag = 715;


#pragma region GridManager
	GridManager* temp = SCENEMANAGER->getGridManager();
	GridManager*  newManager = new GridManager(11);
	SCENEMANAGER->SetGridManager(newManager);
	temp->RemoveAll();
	temp->Clear();
	temp = NULL;
	delete temp;

	for (int i = 0; i < 2; i++) {
		GridContainer* grid = new GridContainer(3072 + i * GRIDCONTAINER_WIDTH, 383);
		SCENEMANAGER->getGridManager()->AddContainer(grid);
	}

	LOADHELPER->LoadObject(OBJECTS_MAP1_FILEPATH);

	//SIMON->x = 3900;/*3552*//*1760*/;/*2816;*//*1248;*/
	//SIMON->y = 50;
	//CAMERA->x = SIMON->xCenter() - CAMERA->width / 2;

	//test basement
	//SIMON->SetPosition(/*3205 + 16*/3931/*3500*/, 416);
	//CAMERA->SetPosition(SIMON->xCenter() - CAMERA->width + 50, 382);
	//CAMERA->SetCornerBlock(3072, 4096);
	//FlagDownBasement = true;
	//FlagAboveBasement = false;

	//-------------------------------------------------------------------------------------------------------//
	//
	SIMON->SetPosition(100/*5220*//*3010*/, /*150*/50);
	CAMERA->SetPosition(0, 0);
	/*CAMERA->x = SIMON->xCenter() - CAMERA->width / 2;*/

	CAMERA->SetCornerBlock(0, 5600);

	LPITEM item = new Item(OBJ_ITEM_CROSS);
	item->SetPosition(200, 100);
	SCENEMANAGER->getGridManager()->AddObject(item);

#pragma region Brickss

	CGround* brickSP1 = new CGround(3, true);
	brickSP1->SetPosition(3584.0f, 320);
	SCENEMANAGER->getGridManager()->AddObject(brickSP1);

	CGround* brickSP2 = new CGround(2, true, false, true, OBJ_ITEM_PORKCHOP);
	brickSP2->SetPosition(3584.0f, 288);
	SCENEMANAGER->getGridManager()->AddObject(brickSP2);

#pragma endregion


#pragma region Candles	

	LPSTATIC candle = new Static();
	candle->id = OBJ_STATIC_CANDLE;
	candle->SetPosition(3000, 60);
	candle->SetItem(OBJ_ITEM_CROSS);
	SCENEMANAGER->getGridManager()->AddObject(candle);

#pragma endregion


	boss = new CVampireBat(ENEMY_VAMPIRE_BAT_POSX - 150, ENEMY_VAMPIRE_BAT_POSY - 30, Right);
	SCENEMANAGER->getGridManager()->AddObject(boss);
	OutputDebugString(("BOSS ID: " + std::to_string(boss->id) + "\n ").c_str());
#pragma endregion


}

void CScene_Level1::update(DWORD time, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPGAMEOBJECT> coObjectsList;
	SCENEMANAGER->getGridManager()->SetCoObjects(coObjectsList);
	SIMON->Update(time, &coObjectsList);
	SIMON->getWeapon()->Update(time, &coObjectsList);
	SCENEMANAGER->getGridManager()->Update(time, &coObjectsList);


	// ground -> basement
#pragma region groundToBasement
	if (SIMON->y > yFlagBasementStairDown && !FlagDownBasement /*&& FlagAboveBasement*/) {
		if (SIMON->typeStairing == ObjectSpecial::STAIRDOWN_LTR && SIMON->IsStairing) {
			if (SIMON->x < 3470) {
				SIMON->SetPosition(3205 + 16, 416);
				CAMERA->SetPosition(3072, 382);
			}
			else {
				SIMON->SetPosition(3874 - 16, 416);
				CAMERA->SetPosition(4096 - CAMERA->width, 382);
			}
			/*CAMERA->SetCornerBlock(3072, 4096);*/
			CAMERA->SetCornerBlock(3072, 4096);
			FlagDownBasement = true;
		}
	}
	else {
		//basement ->  ground
		if (SIMON->y < yFlagBasementStairUp && FlagDownBasement/* && !FlagAboveBasement*/) {
			if (SIMON->typeStairing == ObjectSpecial::STAIRUP_RTL && SIMON->IsStairing) {
				if (SIMON->x < 3470) {
					SIMON->SetPosition(3180, 308);
					CAMERA->SetPosition(SIMON->x - CAMERA->width / 2, 0);
				}
				else {
					SIMON->SetPosition(3840 - 16, 308);
					CAMERA->SetPosition(SIMON->xCenter() - CAMERA->width / 2, 0);
				}
				CAMERA->SetCornerBlock(0, 5600);
				FlagDownBasement = false;

			}
		}
	}
#pragma endregion

	//bossArea
#pragma region BossArea
	if (SIMON->x > xBoosFlag) {
		if (!CAMERA->isLocked) {
			CAMERA->Lock();
			CAMERA->SetCornerBlock(CAMERA->x, CAMERA->x + CAMERA->width);
			boss->startCombat();
			boss->setArea(CAMERA->x, 0, CAMERA->x + CAMERA->width, 382);
		}
	}
#pragma endregion



	OutputDebugString(("x: " + std::to_string(SIMON->x) + ", y: " + std::to_string(SIMON->y) + "\n ").c_str());
	//OutputDebugString(("typeStairing: " + std::to_string(SIMON->typeStairing) + "\n ").c_str());
	/*OutputDebugString(("x: " + std::to_string(CAMERA->leftCornerBlock) + ", y: " + std::to_string(CAMERA->rightCornerBlock) + "\n ").c_str());*/
	//if (FlagDownBasement) OutputDebugString("under basement \n");
}

void CScene_Level1::draw()
{
	bgmap->Render();

	SCENEMANAGER->getGridManager()->Render();
	SIMON->Render();
	SIMON->getWeapon()->Render();
	VISUALFIGURES->Render();


}

CScene_Level1::CScene_Level1()
{

}


CScene_Level1::~CScene_Level1()
{
	delete bgmap;
}
