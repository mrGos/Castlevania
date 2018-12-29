#include "CStage.h"

void CStage::RebornHandle()
{
	stageNumber++;
	if (stageNumber == 0) {
		xReborn = 100.0f;
		yReborn = 100.0f;
	}
	else if (stageNumber == 1) {
		xReborn = 3480.0f;
		yReborn = 76.0f;
	}
	else if (stageNumber == 2) {
		xReborn = 4176.0f;
		yReborn = 76.0f;
	}
}

CStage::CStage()
{
	xReborn = 100.0f;
	yReborn = 100.0f;
}


CStage::~CStage()
{
}
