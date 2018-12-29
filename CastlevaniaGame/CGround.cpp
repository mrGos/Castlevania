#include "CGround.h"
#include "CGameWorld.h"
#include "CSceneManager.h"

CGround::CGround(int groundNum, bool IsAbleBreak, bool IsStairFlag, bool IsItem, int itemID)
{
	id = OBJ_ID::OBJ_GROUND;
	type = TeamType::GROUND;
	vx = 0;
	vy = 0;
	width = height = 32;

	SetState(ObjectState::ALIVE);

	this->IsAbleBreak = IsAbleBreak;
	this->IsStairFlag = IsStairFlag;

	if (IsItem) {
		this->IsItem = IsItem;
		this->itemID = itemID;
	}

	if (groundNum == 0) {
		sprite = SPRITES->Get(ID_GROUND_INTRO);
	}
	else if (groundNum == 1) {
		sprite = SPRITES->Get(ID_GROUND);
	}
	else if (groundNum == 2) {
		sprite = SPRITES->Get(ID_GROUND2);
	}
	else {
		sprite = SPRITES->Get(ID_GROUND3);
	}

}

CGround::CGround(float x, float y, int width, int height, bool IsNoneRender)
{
	SetPosition(x, y);
	SetSize(width, height);
	this->IsNoneRender = IsNoneRender;
}

void CGround::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + 32;
	b = y + 32;
}

void CGround::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (IsAbleBreak) {
		if (GetState() == ObjectState::BURN) {
			if (IsItem) {
				LPITEM item = new Item(itemID);
				item->x = this->x + 0.9f;
				item->y = this->y + height / 2;
				//SCENEMANAGER->getObjManager()->Add(item);
				SCENEMANAGER->getGridManager()->AddObject(item);
			}
			SetState(ObjectState::DIE);
		}
	}
}

void CGround::Render()
{
	if (IsNoneRender) {
		RenderBoundingBox();
		return;
	}
	//RenderBoundingBox();
	//SPRITES->Get(ID_GROUND)->Draw(this->x - GAMEWORLD->getCamera()->x, this->y - GAMEWORLD->getCamera()->y);
	if (!IsStairFlag)
		sprite->Draw(this->x - GAMEWORLD->getCamera()->x, this->y - GAMEWORLD->getCamera()->y);
}


CGround::~CGround()
{
}
