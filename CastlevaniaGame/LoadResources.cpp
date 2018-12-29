#include "LoadResources.h"

LoadResources* LoadResources::_instance = 0;
LoadResources * LoadResources::getInstance()
{
	if (_instance == 0)
		_instance = new LoadResources();
	return _instance;
}

LoadResources::LoadResources()
{

}


void LoadResources::InitResources()
{
	if (!LoadTextures() || !LoadSprites() || !LoadAnimations())
		MessageBox(WINDOW->getWindowHandler(), "failed to initialize resources", "Error", MB_ICONERROR);
}

bool LoadResources::LoadTextures()
{
	try {
		TEXTURES->Add(ID_TEX_BBOX, TEX_BBOX_FILEPATH, D3DCOLOR_XRGB(255, 255, 255));
		TEXTURES->Add(1, "gamedata\\Resources\\simonTEX.png", D3DCOLOR_XRGB(255, 0, 255));
		TEXTURES->Add(4000, ITEM_TEXTURE_PATH, D3DCOLOR_XRGB(255, 0, 255));
		TEXTURES->Add(MENU_BACKGROUND_ID, MENU_BACKGROUND_FILEPATH, D3DCOLOR_XRGB(1, 1, 1));
		TEXTURES->Add(ENTER_BACKGROUND_ID, ENTER_BACKGROUND_FILEPATH, D3DCOLOR_XRGB(1, 1, 1));
		TEXTURES->Add(INTRO_BACKGROUND_ID, INTRO_BACKGROUND_FILEPATH, D3DCOLOR_XRGB(1, 1, 1));
		TEXTURES->Add(2, "gamedata\\Resources\\Map\\intro\\intro_tilesheet.png", D3DCOLOR_XRGB(1, 1, 1));
		TEXTURES->Add(3, "gamedata\\Resources\\Map\\lv1\\lv1.png", D3DCOLOR_XRGB(1, 1, 1));
		TEXTURES->Add(VISUALINFO_BACKGROUND_ID, VISUALINFO_BACKGROUND_PATH, D3DCOLOR_XRGB(1, 1, 1));
		TEXTURES->Add(GAMEWIN_ID, GAMEWIN_PATH, D3DCOLOR_XRGB(1, 1, 1));
		TEXTURES->Add(GAMEOVER_ID, GAMEOVER_PATH, D3DCOLOR_XRGB(1, 1, 1));

	}
	catch (...) {
		return false;
	}
	return true;
}

bool LoadResources::LoadSprites()
{

	SPRITES->Add(MENU_BACKGROUND_ID, 0, 0, 552, 384, TEXTURES->Get(MENU_BACKGROUND_ID));
	SPRITES->Add(ENTER_BACKGROUND_ID, 0, 0, 552, 384, TEXTURES->Get(ENTER_BACKGROUND_ID));			//test
	SPRITES->Add(INTRO_BACKGROUND_ID, 0, 0, 1536, 384, TEXTURES->Get(INTRO_BACKGROUND_ID));			//test
	SPRITES->Add(VISUALINFO_BACKGROUND_ID, 0, 0, 552, 68, TEXTURES->Get(VISUALINFO_BACKGROUND_ID));
	SPRITES->Add(GAMEWIN_ID, 0, 0, 552, 384, TEXTURES->Get(GAMEWIN_ID));
	SPRITES->Add(GAMEOVER_ID, 0, 0, 552, 384, TEXTURES->Get(GAMEOVER_ID));

	if (!ReadSpriteFile(SIMON_DATA_FILEPATH, 1) || !ReadSpriteFile(ITEM_SPRITE_PATH, 4000))
		return false;
	if (!ReadSpriteFile(INTRO_TILESHEET_INFO_FILEPATH, 2))
		return false;
	if (!ReadSpriteFile(MAP1_TILESHEET_INFO_FILEPATH, 3, 10000))
		return false;
	return true;
}

bool LoadResources::LoadAnimations()
{
	if (!ReadAnimationFile(SIMON_ANIM_FILEPATH) || !ReadAnimationFile(ITEM_ANIM_FILEPATH))
		return false;
	return true;

}

bool LoadResources::LoadObject(const char* filePath)
{
	if (ReadObject(filePath))
		return true;
	return false;
}

LoadResources::~LoadResources()
{

}
