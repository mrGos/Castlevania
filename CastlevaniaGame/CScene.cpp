#include "CScene.h"

CScene* CScene::curScene = 0;
void CScene::changeScene(CScene* scene, bool clean)
{
	if (curScene != 0 && clean)
	{
		delete curScene;
		curScene = NULL;
	}


	curScene = scene;
	curScene->init();
}

CScene::CScene(void)
{
}


CScene::~CScene(void)
{
}
