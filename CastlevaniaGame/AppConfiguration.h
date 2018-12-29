#pragma once
#define CLASS_NAME "CastleGame"
#define TITLE_STR "Castle Vania UITK11"

#define SCREEN_WIDTH							640
#define SCREEN_HEIGHT							480

#define DIRECTINPUT_VERSION						0x0800
#define KEYBOARD_BUFFER_SIZE					1024

#define GAME_FONT								"gamedata\\font\\prstart.ttf"
#define SPRITE_BLACK_BG							
#define TEXT_COLOR_DEFAULT						D3DCOLOR_XRGB(255, 255, 255)
#define TEXT_FIGURES_GAME						"SCORE-0       TIME 0    STAGE 0  \nPLAYER                 = \nENEMY                P = \n";
#define TEXT_NUMBER_SIZE						 16					

#define WINDOW									CWindow_Screen::getInstance()
#define GRAPHICS								CGraphics::getInstance()
#define SPRITES									CSprites::getInstance()
#define TEXTURES								CTextures::getInstance()
#define ANIMATIONS								CAnimations::getInstance()
#define GAMEWORLD								CGameWorld::getInstance()
#define SCENEMANAGER							CSceneManager::getInstance()
#define KEYBOARD								CKeyboard::getInstance()
#define KEYHANDLER								CKeyEventHandler::getInstance()
#define GAMESTATE								CGameState::getInstance()
#define CAMERA									Camera::getInstance()
#define VISUALFIGURES							CVisualFigures::getInstance()
#define GAMESOUND								GameSound::getInstance()
#define WHIP									CWhip::getInstance()
#define LOADHELPER								LoadResources::getInstance()

#define AUDIO_FORMAT_TAG		WAVE_FORMAT_PCM
#define	AUDIO_NUM_OF_CHANNEL	2
#define AUDIO_SAMPLE_SPEED		22050
#define AUDIO_BITS_PER_SAMPLE	16
#define AUDIO_FLAGS				0
#define AUDIO_BUFFER_SIZE		640000
#define AUDIO_GUID				GUID_NULL
#define AUDIO_BLOCK_ALIGN(bitPerSample, nChannels)		(WORD)(bitPerSample / 8 * nChannels)
#define AUDIO_AVERAGE_BPS(samplesPerSec, blockAlign)	(DWORD)(samplesPerSec * blockAlign)

#define MUSIC_LEVEL1_PATH						"gamedata\\Sounds\\music\\Stage_01_Vampire_Killer.wav"	
#define MUSIC_GAMESTART_PATH					"gamedata\\Sounds\\music\\Game_Start_Prologue.wav"	
#define MUSIC_VAMPIREBAT_PATH					"gamedata\\Sounds\\music\\Boss_Battle_Poison_Mind.wav"	
#define MUSIC_BOSS_DEFEATED_PATH				"gamedata\\Sounds\\music\\Stage_Clear.wav"	
#define MUSIC_LOST_LIFENUMBER_PATH				"gamedata\\Sounds\\music\\Life_Lost.wav"
#define MUSIC_GAMEOVER_PATH						"gamedata\\Sounds\\music\\Game_Over.wav"

#define SOUND_WHIP_PATH							"gamedata\\Sounds\\sound\\usingwhip.wav"
#define SOUND_HIT_PATH							"gamedata\\Sounds\\sound\\hit.wav"
#define SOUND_COLLECTITEM_PATH					"gamedata\\Sounds\\sound\\collectitem.wav"
#define SOUND_COLLECTWEAPON_PATH				"gamedata\\Sounds\\sound\\collectweapon.wav"
#define SOUND_DAGGER_PATH						"gamedata\\Sounds\\sound\\dagger_throw.wav"
#define SOUND_HOLLYWATER_PATH					"gamedata\\Sounds\\sound\\holywater.wav"
#define SOUND_AXE_PATH							"gamedata\\Sounds\\sound\\axe_throw.wav"
#define SOUND_BOOMERANG_PATH					"gamedata\\Sounds\\sound\\boomerang_throw.wav"
#define SOUND_DOOR_PATH							"gamedata\\Sounds\\sound\\door.wav"
#define SOUND_BRICK_BROKEN_PATH					"gamedata\\Sounds\\sound\\brickbroken.wav"
#define SOUND_CHECKPOINT_PATH					"gamedata\\Sounds\\sound\\checkpoint.wav"

#define MENU_BACKGROUND_FILEPATH				"gamedata\\Resources\\Background\\start_game.png"
#define MENU_BACKGROUND_ID						9999
#define ENTER_BACKGROUND_FILEPATH				"gamedata\\Resources\\Background\\enter.png"
#define ENTER_BACKGROUND_ID						9998
#define INTRO_BACKGROUND_FILEPATH				"Data\\Map\\intro\\intro.png"
#define INTRO_BACKGROUND_ID						9997

#define LEVEL1_TILE_BACKGROUNDMAP_FILEPATH		"gamedata\\Resources\\Map\\lv1\\lv1_BGMap.txt"

#define VISUALINFO_BACKGROUND_PATH				"gamedata\\Resources\\blackboard.png"
#define VISUALINFO_BACKGROUND_ID				9996
#define GAMEWIN_PATH							"gamedata\\Resources\\Background\\GameWin.png"
#define GAMEWIN_ID								9995
#define GAMEOVER_PATH							"gamedata\\Resources\\Background\\GameEnd.png"
#define GAMEOVER_ID								9994

#define SIMON_ANIM_FILEPATH						"gamedata\\Resources\\AnimSimonTEX.txt"

#define ITEM_TEXTURE_PATH						"gamedata\\Resources\\item\\items.png"
#define ITEM_SPRITE_PATH						"gamedata\\Resources\\item\\itemsSPRITE.txt"
#define ITEM_ANIM_FILEPATH						"gamedata\\Resources\\item\\itemsANIM.txt"

#define OBJECTS_MAP1_FILEPATH					"gamedata\\Resources\\Map\\lv1\\Objects.txt"
#define OBJECTS_INTRO_FILEPATH					"gamedata\\Resources\\Map\\intro\\Objects.txt"

#define SUBWEAPON_DAMAGE_DEFAULT				3
#define SUBWEAPON_DAGGER_WIDTH					40
#define SUBWEAPON_DAGGER_HEIGHT					22
#define SUBWEAPON_DAGGER_VELOCITY_X				0.7f
#define SUBWEAPON_AXE_WIDTH						37
#define SUBWEAPON_AXE_HEIGHT					35
#define SUBWEAPON_AXE_VELOCITY_X				0.3f
#define SUBWEAPON_AXE_VELOCITY_Y				0.8f
#define SUBWEAPON_BOOMERANG_VELOCITY_X			0.4f

#define HP_DEFAULT								1
#define ENEMY_DAMAGE_DEFAULT					1

#define ENEMY_GHOST_WIDTH						30
#define ENEMY_GHOST_HEIGHT						67
#define ENEMY_GHOST_VELOCITY_X					0.15f

#define ENEMY_BAT_WIDTH							37
#define ENEMY_BAT_HEIGHT						31
#define ENEMY_BAT_VELOCITY_X					0.15f

#define ENEMY_DOG_WIDTH							64
#define ENEMY_DOG_HEIGHT						30		

#define ENEMY_FISHMAN_WIDTH						34
#define ENEMY_FISHMAN_HEIGHT					65		
#define ENEMY_FISHMAN_VELOCITY_X				0.04f
#define ENEMY_FISHMAN_VELOCITY_Y				0.6f
#define ENEMY_FISHMAN_GRAVITY					0.0012f

#define ENEMY_VAMPIRE_BAT_POSX					5340.0f 
#define ENEMY_VAMPIRE_BAT_POSY					112.0f 
#define ENEMY_VAMPIRE_BAT_WIDTH					81 
#define ENEMY_VAMPIRE_BAT_HEIGHT				57 

#define PI										3.14159265

#define BACKGROUND_COLOR						D3DCOLOR_XRGB(0,0,0)
#define VIEWPORT_WIDTH							552
#define VIEWPORT_HEIGHT							382/*382*/
#define BACK_WIDTH								VIEWPORT_WIDTH
#define BACK_HEIGHT								VIEWPORT_HEIGHT
#define MAX_FRAME_RATE							60

#define CAMERA_UPDATE_RIGHT					VIEWPORT_WIDTH*0.4
#define CAMERA_UPDATE_LEFT					VIEWPORT_WIDTH*0.2
#define CAMERA_UPDATE_BOTTOM				VIEWPORT_HEIGHT*2/3
#define CAMERA_UPDATE_TOP					VIEWPORT_HEIGHT/3
#define LEFT_CAMERA_INTRO_BLOCK					0
#define RIGHT_CAMERA_INTRO_BLOCK				1504

#define GRIDCONTAINER_WIDTH						512.0f

#define SIMON									CSimon::getInstance()
#define SIMON_FULL_HP							16
#define SIMON_FULL_WEAPONLEVEL					3
#define SIMON_WALKING_SPEED						0.2f
#define SIMON_WALKING_CASTLE_SPEED				0.065f
#define SIMON_JUMP_SPEED_Y						0.5f
#define SIMON_JUMP_DEFLECT_SPEED				0.2f
#define SIMON_GRAVITY							0.002f
#define ITEM_GRAVITY							0.00098f
#define SIMON_DOWN_BOX_HEIGHT					15.0f
#define SIMON_TIME_DURING_ATTACK				300

#define WHIP_DAMAGE								1

#define TIME_DURING_BURN						300

#define ID_TEX_BBOX								-100
#define ID_GROUND								333
#define ID_GROUND2								334
#define ID_GROUND3								335
#define ID_GROUND_INTRO							336

#define TILE_SIZE								32

#define ID_SPRITE_REDHP							6155
#define ID_SPRITE_ORANGEHP						6156
#define ID_ANIM_SIMON_DOWNSTAIR					5061
#define ID_ANIM_SIMON_UPSTAIR					5071