#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <stdio.h>
//#include "dxgraphics.h"


#include "CGamePanel.h"
#include "AppConfiguration.h"



//đầu vào ứng dụng Window
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {


	//khởi tạo game

	CGamePanel* game = new CGamePanel(hInstance, nCmdShow);
	game->GameLoop();

	return 0;
}