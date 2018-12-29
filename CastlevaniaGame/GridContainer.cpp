#include "GridContainer.h"
#include "CGameWorld.h"
#include <algorithm>

GridContainer::GridContainer(float x, float y)
{
	width = GRIDCONTAINER_WIDTH;
	height = 382.0f;
	this->x = x;
	this->y = y;
}


GridContainer::~GridContainer()
{
}


void GridContainer::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void GridContainer::Render()
{
	//RenderBoundingBox();
	for (int i = 0; i < listObjectInGrid.size(); i++) {
		listObjectInGrid[i]->Render();
	}

}

void GridContainer::SetListObject(vector<LPGAMEOBJECT> listObj)
{
	for (int i = 0; i < listObjectInGrid.size(); i++) {
		listObj.push_back(listObjectInGrid[i]);
	}
}

void GridContainer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//int k = listObjectInGrid.size();
	for (int i = 0; i < listObjectInGrid.size(); i++) {
		listObjectInGrid[i]->Update(dt, coObjects);
		//add code v2
		//earase obj if out of list

		if (/*(!AABBCheck(*this, *listObjectInGrid[i]) && listObjectInGrid[i]->type == TeamType::ENEMY)
			|| (!AABBCheck(*this, *listObjectInGrid[i]) && listObjectInGrid[i]->type == TeamType::WEAPON)||*/
			listObjectInGrid[i]->GetState() == ObjectState::DIE) {

			/*listObjectInGrid.erase(std::remove(listObjectInGrid.begin(), listObjectInGrid.end(), listObjectInGrid[i]));*/
			listObjectInGrid.erase(listObjectInGrid.begin() + i);

		}

	}
}

void GridContainer::RemoveAllObject()
{
	for (std::vector< LPGAMEOBJECT >::iterator it = listObjectInGrid.begin(); it != listObjectInGrid.end(); ++it)
	{
		delete (*it);
	}
	listObjectInGrid.clear();
}

bool GridContainer::isOutOfCamera()
{
	if (!AABBCheck(*GAMEWORLD->getCamera(), *this))
	{
		return true;
	}
	else
	{
		return false;
	}
}
