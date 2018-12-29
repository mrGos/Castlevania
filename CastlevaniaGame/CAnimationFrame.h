#pragma once
#include "CSprites.h"
#include "AppConfiguration.h"

class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	void SetTime(DWORD time) { this->time = time; }

	LPSPRITE GetSprite() { return sprite; }
	int getHeight() { return this->sprite->getHeight(); }
	int getWidth() { return this->sprite->getWidth(); }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

