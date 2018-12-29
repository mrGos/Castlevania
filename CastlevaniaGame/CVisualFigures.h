#pragma once
#include "CGameObject.h"
#include "CGraphics.h"
#include <string>

using namespace std;

class CVisualFigures : public CGameObject
{
	ID3DXFont *font;



	bool IsChangeScene; //or changeScene
	DWORD timeStartPrepareChangeScene;
	int timeDuringPrepareChangeScene = 2000;

	string strGameFiguresInfomation = "";
	string strTestGame = "";
	string strTxtBoard = "";


	static CVisualFigures*  _instance;
	CVisualFigures();
public:
	int timeCount = 300;
	DWORD timeStartCount;
	DWORD timeDuringCount = 1000;


	bool IsCheckPoint;
	bool IsStopTime;

	static CVisualFigures* getInstance();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void RenderVisualImage();
	~CVisualFigures();
};

