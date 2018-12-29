#include "CGameWorld.h"
#include "CScene_Menu.h"
#include "CSceneManager.h"

//vector<LPGAMEOBJECT> objects;


CGameWorld* CGameWorld::_instance = 0;

CGameWorld::CGameWorld()
{

	/*bgmap = new BackgroundMap();
	bgmap->InitMap("gamedata\\Resources\\Map\\intro\\IntroBGMap.txt");*/


	/*objManager = new CGameObjectManager();*/

	/*camera = new Camera(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);*/
	camera = Camera::getInstance();
	//graphics = GRAPHICS;
	//keyboard = KEYBOARD;
	//sceneManager = SCENEMANAGER;
	//visual = VISUALFIGURES;

	GAMESOUND->initialize(WINDOW->getWindowHandler());
	LOADHELPER->InitResources();
	LPKEYEVENTHANDLER keyGame = new CKeyGameHandler();
	KEYBOARD->InitKeyboard(keyGame);

	VISUALFIGURES->IsStopTime = true;
	SCENEMANAGER->changeScene(new CScene_Menu());
	//SCENEMANAGER->changeScene(new CScene_Level1());

}


CGameWorld * CGameWorld::getInstance()
{
	if (_instance == 0)
		_instance = new CGameWorld();
	return _instance;
}



void CGameWorld::Update(DWORD time)
{


	KEYBOARD->ProcessKeyboard();

	SCENEMANAGER->update(time);
	camera->Update(time);
	/*VISUALFIGURES->Update(time);*/

}

void CGameWorld::Render()
{


	GRAPHICS->BeginGraphics();
	// Clear back buffer with a color
	GRAPHICS->GetDirect3DDevice()->ColorFill(GRAPHICS->GetBackBuffer(), NULL, BACKGROUND_COLOR);

	//spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	SCENEMANAGER->draw();

	/*visual->Render();*/
	GRAPHICS->EndGraphics();


	GRAPHICS->PresentBackBuffer();
}

CGameWorld::~CGameWorld()
{

	delete GAMESTATE;
	delete CAMERA;
	delete ANIMATIONS;
	delete SCENEMANAGER;
	delete SPRITES;
	delete TEXTURES;
	delete GAMEWORLD;
	delete KEYBOARD;
	delete GRAPHICS;
	delete WINDOW;
	delete SIMON;
}
