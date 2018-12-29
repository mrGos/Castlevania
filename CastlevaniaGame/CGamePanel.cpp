#include "CGamePanel.h"



CGamePanel::CGamePanel()
{
}

CGamePanel::CGamePanel(HINSTANCE hInstance, int nCmdShow)
{
	WINDOW->Init_WindowHandler(hInstance, nCmdShow);

	if (!GRAPHICS) {
		return;
	}
}


CGamePanel::~CGamePanel()
{
	delete WINDOW;
	delete GRAPHICS;
}

void CGamePanel::GameLoop()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / (MAX_FRAME_RATE*1.2);

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			//game->ProcessKeyboard();

			//Update(dt);
			GAMEWORLD->Update(dt);
			GAMEWORLD->Render();
			//Render();

		}
		else
		{
			//timeBeginPeriod(1);
			Sleep(tickPerFrame - dt);
			//timeEndPeriod(1);
		}
	}
}
