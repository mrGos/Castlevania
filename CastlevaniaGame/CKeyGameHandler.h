#pragma once
#include <Windows.h>
#include "CKeyboard.h"
#include "CGameState.h"
#include "CSimon.h"



class CKeyGameHandler : public CKeyEventHandler
{
public:
	CKeyGameHandler();
	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	~CKeyGameHandler();
};

