#include "CDoor.h"
#include "CGameWorld.h"


CDoor::CDoor()
{
}

void CDoor::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (IsOpen) {
		if (CAMERA->x < xOffsetCameraAfterUpdate) {
			CAMERA->x += vx * dt;
		}
		else {

			if (SIMON->x < xOffsetPlayerAfterUpdate) {
				if (!IsUpdatePlayerState) SIMON->SetState(MOVE);
			}
			else {
				SIMON->SetState(IDLE);
				IsUpdatePlayerState = true;
				GAMESOUND->play(SOUND_DOOR_PATH);
				(SIMON->direction == Right) ? CAMERA->leftCornerBlock = xOffsetCameraAfterUpdate : CAMERA->rightCornerBlock = xOffsetCameraAfterUpdate;
				GAMESTATE->IsLockingKeyBoard = false;
				SetState(ObjectSpecial::DOOR_CLOSE_ACTIVE);

				AnimDoorOpenActive->resetAnim();
				AnimDoorCloseActive->resetAnim();
			}
		}
	}
}

void CDoor::Render()
{
	switch (state) {
	case ObjectSpecial::DOOR_IDLE:
		AnimDoorClose->Render(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, false, false);
		break;
	case ObjectSpecial::DOOR_OPEN_ACTIVE:
		AnimDoorOpenActive->Render(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, false, false);
		break;
	case ObjectSpecial::DOOR_CLOSE_ACTIVE:
		AnimDoorCloseActive->Render(x - GAMEWORLD->getCamera()->x, y - GAMEWORLD->getCamera()->y, 255, false, false);
		break;
	default:
		break;
	}

	//RenderBoundingBox();
}

void CDoor::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state) {
	case ObjectSpecial::DOOR_OPEN_ACTIVE:
		IsOpen = true;
		vx = 0.15*SIMON->direction;
		break;
	case ObjectSpecial::DOOR_CLOSE_ACTIVE:
		IsOpen = false;
		vx = 0.0f;
		break;
	default:
		break;
	}
}


CDoor::CDoor(float posx, float posy)
{
	id = ObjectSpecial::DOOR_IDLE;
	type = TeamType::DOOR;
	SetState(ObjectSpecial::DOOR_IDLE);

	CGameObject::InitPosition(posx, posy);
	width = 19;
	height = 74;

	AnimDoorClose = ANIMATIONS->Get(ObjectSpecial::DOOR_IDLE);
	AnimDoorOpenActive = ANIMATIONS->Get(ObjectSpecial::DOOR_OPEN_ACTIVE);
	AnimDoorCloseActive = ANIMATIONS->Get(ObjectSpecial::DOOR_CLOSE_ACTIVE);
}

CDoor::~CDoor()
{
}
