#include "Grid.h"
#include "CGameWorld.h"


void GridManager::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < listGridContainer.size(); i++) {

		//LPGRIDCONTAINER containerInList = (LPGRIDCONTAINER)listGridContainer[i];

		if (!listGridContainer[i]->isOutOfCamera())
		{
			listGridContainer[i]->Update(dt, coObjects);
		}
	}
}

void GridManager::Render()
{
	for (int i = 0; i < listGridContainer.size(); i++) {
		if (!listGridContainer[i]->isOutOfCamera()) {
			listGridContainer[i]->Render();
		}
	}
}

void GridManager::SetListObjectInCamera(vector<LPGAMEOBJECT>listObjInCamera)
{
	for (int i = 0; i < listGridContainer.size(); i++) {
		if (!listGridContainer[i]->isOutOfCamera()) {
			listGridContainer[i]->SetListObject(listObjInCamera);
		}
	}
}

void GridManager::AddContainer(LPGRIDCONTAINER gobj)
{
	listGridContainer.push_back(gobj);
	//OutputDebugString(("size: " + std::to_string(listGridContainer.size())  + "\n ").c_str());
}

void GridManager::AddObject(LPGAMEOBJECT obj)
{
	for (int i = 0; i < listGridContainer.size(); i++) {
		if (AABBCheck(*listGridContainer[i], *obj)) {
			listGridContainer[i]->Add(obj);
			return;
		}
	}
}

void GridManager::Clear()
{
	listGridContainer.clear();
}

void GridManager::RemoveAll()
{
	for (std::vector< LPGRIDCONTAINER >::iterator it = listGridContainer.begin(); it != listGridContainer.end(); ++it)
	{
		delete (*it);
	}
	listGridContainer.clear();
}

void GridManager::SetCoObjects(vector<LPGAMEOBJECT> &l)
{
	for (int i = 0; i < listGridContainer.size(); i++) {
		if (!listGridContainer[i]->isOutOfCamera()) {
			for (int j = 0; j < listGridContainer[i]->listObjectInGrid.size(); j++) {
				l.push_back(listGridContainer[i]->listObjectInGrid[j]);
			}
		}
	}
}

GridManager::GridManager()
{
}

GridManager::GridManager(int n)
{
	for (int i = 0; i < n; i++) {
		LPGRIDCONTAINER container = new GridContainer(0 + i * GRIDCONTAINER_WIDTH, 0);
		listGridContainer.push_back(container);
	}
}


GridManager::~GridManager()
{
}

