#pragma once
#include <Windows.h>
#include "CGameObject.h"
void SweptAABB(
	float ml,			// move left 
	float mt,			// move top
	float mr,			// move right 
	float mb,			// move bottom
	float dx,			// 
	float dy,			// 
	float sl,			// static left
	float st,
	float sr,
	float sb,
	float &t,
	float &nx,
	float &ny);

bool AABBCheck(CDObject & M, CDObject & S);
bool AABBCheckORI(LPGAMEOBJECT  M, LPGAMEOBJECT  S);
bool AABBCheckMoving(LPGAMEOBJECT  M, LPGAMEOBJECT  S);
void DrawNumber(int number, float x, float y, int alpha = 255);
