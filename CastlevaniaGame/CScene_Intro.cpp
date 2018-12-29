#include "CScene_Intro.h"
#include "CGameWorld.h"
#include "CSceneManager.h"



void CScene_Intro::init()
{
	//SIMON->gy = 0;


	bgmap = new BackgroundMap();
	bgmap->InitMap("gamedata\\Resources\\Map\\intro\\IntroBGMap.txt");


	GAMESTATE->currentMusic = MUSIC_LEVEL1_PATH;
	GAMESOUND->play(GAMESTATE->currentMusic, true);

	CAMERA->SetCornerBlock(0, 1504);
#pragma region Grid

	GridManager* temp = SCENEMANAGER->getGridManager();
	GridManager*  newManager = new GridManager(3);
	SCENEMANAGER->SetGridManager(newManager);
	temp->RemoveAll();
	temp->Clear();
	delete temp;

	LOADHELPER->LoadObject(OBJECTS_INTRO_FILEPATH);

	SIMON->x = 100;
}

void CScene_Intro::update(DWORD time, vector<LPGAMEOBJECT> *coObjects)
{

#pragma region updateGrid
	vector<LPGAMEOBJECT> coObjectsList;
	SCENEMANAGER->getGridManager()->SetCoObjects(coObjectsList);
	SCENEMANAGER->getGridManager()->Update(time, &coObjectsList);
	SIMON->Update(time, &coObjectsList);
	SIMON->getWeapon()->Update(time, &coObjectsList);

	OutputDebugString(("x: " + std::to_string(SIMON->x) + ", y: " + std::to_string(SIMON->y) + "\n ").c_str());
#pragma endregion

	if (SIMON->x > xLeftFlagSlowSpeed && SIMON->x < XRightFlagSlowSpeed) {
		GAMESTATE->IsLockingKeyBoard = true;
		SIMON->direction = Right;
		SIMON->IsRunning = true;
		SIMON->SetState(MOVE);
		SIMON->vx = vxSlowDown;
	}

	if (SIMON->x > FlagChangeScene) {
		SIMON->SetState(IDLE);
		//SIMON->IsRunning = false;
		GAMESTATE->IsLockingKeyBoard = false;
		SCENEMANAGER->changeScene(new CScene_Level1(), true);
	}
}

void CScene_Intro::draw()
{
	bgmap->Render();

	SCENEMANAGER->getGridManager()->Render();
	SIMON->Render();
	SIMON->getWeapon()->Render();
	VISUALFIGURES->Render();
}

CScene_Intro::CScene_Intro()
{
}


CScene_Intro::~CScene_Intro()
{
}
