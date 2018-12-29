#pragma once




class CStage
{
public:
	int stageNumber = 0;
	float xReborn, yReborn;

	void RebornHandle();
	CStage();
	~CStage();
};
typedef CStage* LPSTAGE;

