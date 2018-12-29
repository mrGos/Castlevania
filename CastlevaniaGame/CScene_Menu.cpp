#include "CScene_Menu.h"
#include "CSceneManager.h"
#include "CSceneManager.h"

void CScene_Menu::init()
{
}

void CScene_Menu::update(DWORD time, vector<LPGAMEOBJECT> *coObjects)
{
	if (GAMESTATE->IsStartGame) {

		SCENEMANAGER->changeScene(new CScene_EnterCastle());
	}
}

void CScene_Menu::draw()
{
	menu_background->Draw(0, 0, D3DCOLOR_XRGB(255, 255, 255));
}

CScene_Menu::CScene_Menu()
{
	menu_background = SPRITES->Get(MENU_BACKGROUND_ID);
}


CScene_Menu::~CScene_Menu()
{
}
