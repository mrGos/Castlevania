#include "CSceneManager.h"
#include "CGameState.h"

CSceneManager* CSceneManager::_instance = 0;
CSceneManager * CSceneManager::getInstance()
{
	if (_instance == 0)
		_instance = new CSceneManager();
	return _instance;
}
void CSceneManager::init()
{
}

void CSceneManager::update(DWORD time, vector<LPGAMEOBJECT> *coObjects)
{
	/*vector<LPGAMEOBJECT> coObjectsList;
	for (int i = 1; i < objManager->listGameObjects.size(); i++)
	{
		coObjectsList.push_back(objManager->listGameObjects[i]);
	}*/
	/*curScene->update(time, &coObjectsList);
	VISUALFIGURES->Update(time);*/

#pragma region GridUpdate
	if (GAMESTATE->IsCrossActivated) {
		(GetTickCount() % 2 == 0) ? GRAPHICS->SetColor(255, 255, 255) : GRAPHICS->SetColor(0, 0, 0);
	}

	if (GAMESTATE->IsGameWin) {

	}
	else if (GAMESTATE->IsGameEnd) {

	}
	else {
		curScene->update(time, coObjects);
		VISUALFIGURES->Update(time);
	}

#pragma endregion
}

void CSceneManager::draw()
{
	if (GAMESTATE->IsGameWin) {
		SPRITES->Get(GAMEWIN_ID)->Draw(0, 0);
	}
	else if (GAMESTATE->IsGameEnd) {
		SPRITES->Get(GAMEOVER_ID)->Draw(0, 0);
	}
	else {
		curScene->draw();
		//VISUALFIGURES->Render();
	}

	//VISUALFIGURES->Render();
	/*if (GAMESTATE->IsStartGame)*/

	//VISUALFIGURES->RenderVisualImage();
}

CSceneManager::CSceneManager()
{
	objManager = new CGameObjectManager();
	gridManager = new GridManager();
}


CSceneManager::~CSceneManager()
{
	delete gridManager;
	delete objManager;
}
