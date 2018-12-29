#include "ReadFilesHelper.h"
#include "CGameWorld.h"

using namespace Loader;

bool ReadAnimationFile(const char * filePath) {
	ifstream infile;
	try {
		//LPANIMATION ani;
		//ani = new CAnimation(200);	// idle big right
		//ani->Add(31);
		//ani->Add(32);
		//ani->Add(33);
		//ANIMATIONS->Add(30, ani);
		int time, n, AnimId;
		int spriteId[100];
		//SPRITES->Add(11, 8, 224, 79, 253, TEXTURES->Get(1));
		// mo mot file trong che do read.

		infile.open(filePath);

		while (!infile.eof())
		{
			infile >> time;
			infile >> n;
			infile >> AnimId;
			LPANIMATION ani;
			ani = new CAnimation(time);
			for (int i = 0; i < n; i++) {
				infile >> spriteId[i];
				ani->Add(spriteId[i]);
			}
			ANIMATIONS->Add(AnimId, ani);
		}


		// dong file da mo.
		infile.close();

	}
	catch (...) {
		return false;
		infile.close();
	}
	return true;
}
bool ReadSpriteFile(const char * filePath, int texId, int offset) {
	ifstream infile;
	try {
		int id, left, top, right, bottom;

		//SPRITES->Add(11, 8, 224, 79, 253, TEXTURES->Get(1));
		// mo mot file trong che do read.

		infile.open(filePath);
		if (!infile) {
			MessageBox(WINDOW->getWindowHandler(), "failed to read Sprite data", "Error", MB_ICONERROR);
			return false;
		}

		if (!infile) {
			infile.close();
			return false;
		}

		while (infile >> id >> left >> top >> right >> bottom)
		{
			id += offset;
			SPRITES->Add(id, left, top, right, bottom, TEXTURES->Get(texId));
		}


		// dong file da mo.
		infile.close();
	}
	catch (...) {
		infile.close();
		return false;
	}
	return true;
}

bool ReadObject(const char * filePath)
{
	ifstream infile;
	try {
		int obj;
		float x, y;

		infile.open(filePath);
		if (!infile) {
			MessageBox(WINDOW->getWindowHandler(), "failed to read Object data", "Error", MB_ICONERROR);
			return false;
		}

		if (!infile) {
			infile.close();
			return false;
		}

		while (infile >> obj >> x >> y)
		{
			LPGAMEOBJECT gameObj;
			int  direction = -1;
			if (obj >= 30) {
				infile >> direction;
			}

			switch (obj) {
			case BRICK:
				gameObj = new CGround();
				gameObj->SetPosition(x, y);
				break;
			case BRICK2:
				gameObj = new CGround(2);
				gameObj->SetPosition(x, y);
				break;
			case BRICK3:
				gameObj = new CGround(3);
				gameObj->SetPosition(x, y);
				break;
			case BRICK_INTRO:
				gameObj = new CGround(0);
				gameObj->SetPosition(x, y);
				break;
			case BRICK_FLAG:
				gameObj = new CGround(1, false, true);
				gameObj->SetPosition(x, y);
				break;
			case CANDLE:
				gameObj = new  Static();
				gameObj->id = OBJ_STATIC_CANDLE;
				gameObj->SetPosition(x, y);
				break;
			case TORCH:
				gameObj = new  Static();
				gameObj->SetPosition(x, y);
				break;
			case DOOR:
				gameObj = new CDoor(x, y);
				break;
			case STAIR:
				gameObj = new CStair(x, y, direction);
				break;
			case GHOST:
				gameObj = new CGhost(x, y, direction);
				break;
			case BAT:
				gameObj = new CBat(x, y, direction);
				break;
			case DOG:
				gameObj = new CDog(x, y, direction);
				break;
			case FISHMAN:
				gameObj = new CFishMan(x, y, direction);
				break;
			default: {
				gameObj = new CGround();
				gameObj->SetPosition(x, y);
				break;
			}
			}
			SCENEMANAGER->getGridManager()->AddObject(gameObj);
		}


		// dong file da mo.
		infile.close();
	}
	catch (...) {
		infile.close();
		return false;
	}
	return true;
}
