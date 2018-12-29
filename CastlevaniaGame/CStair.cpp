#include "CStair.h"
#include "CGameWorld.h"


CStair::CStair()
{
}


void CStair::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (AABBCheck(*this, *SIMON)) {
		if (id != ObjectSpecial::STAIR_STOP) {
			SIMON->IsAbleStairing = true;
			SIMON->typeStairing = id;

			if (id == ObjectSpecial::STAIRUP_LTR) {
				SIMON->xStairOffset = x + width / 5;
			}
			else if (id == ObjectSpecial::STAIRUP_RTL) {
				SIMON->xStairOffset = x + width - 32 - 8;
				/*SIMON->xStairOffset = x + 13;*/
			}
			else if (id == ObjectSpecial::STAIRDOWN_LTR) {
				SIMON->xStairOffset = x + width - 5;
			}
			else if (id == ObjectSpecial::STAIRDOWN_RTL) {
				SIMON->xStairOffset = x - 8 - 16;
			}
		}
		else if (id == ObjectSpecial::STAIR_STOP) {
			//OutputDebugString("Collision: true \n ");
			SIMON->IsStairing = false;
			SIMON->IsAbleStairing = false;
			SIMON->SetState(IDLE);
			SIMON->vy += (gy * dt) / 9;
			SIMON->stopRun();
		}
		SIMON->typeStairing = id;
	}
}

void CStair::Render()
{
	//RenderBoundingBox();
}

CStair::CStair(int x, int y, int id, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	type = TeamType::STAIR;
	this->id = id;
	if (id == ObjectSpecial::STAIR_STOP) {
		this->width = 3;
		this->height = 3;
	}

	if (id == ObjectSpecial::STAIRDOWN_LTR || id == ObjectSpecial::STAIRDOWN_RTL) {
		this->width = 32;
		this->height = 32;
	}
}

CStair::~CStair()
{
}
