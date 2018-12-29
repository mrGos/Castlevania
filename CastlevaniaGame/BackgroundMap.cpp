#include "BackgroundMap.h"
#include "AppConfiguration.h"
#include "CGameWorld.h"


void BackgroundMap::Render()
{
	/*for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (matrixMap[i][j] != 0 && (j * tileSize - GAMEWORLD->getCamera()->x) > -30 && (j * tileSize - GAMEWORLD->getCamera()->x) < VIEWPORT_WIDTH
				&& (i * tileSize - GAMEWORLD->getCamera()->y) > -30 && (i * tileSize - GAMEWORLD->getCamera()->y) < VIEWPORT_HEIGHT)
			{
				SPRITES->Get(matrixMap[i][j])->Draw((int)x + j * tileSize - (int)GAMEWORLD->getCamera()->x,
					(int)y + i * tileSize - (int)GAMEWORLD->getCamera()->y);
			}
		}
	}*/
	int rowBegin, rowEnd, columnBegin, columnEnd;
	columnBegin = (int)(GAMEWORLD->getCamera()->x / tileSize);
	columnEnd = (int)(GAMEWORLD->getCamera()->x + GAMEWORLD->getCamera()->width) / tileSize;
	rowBegin = (int)(GAMEWORLD->getCamera()->y) / tileSize;
	rowEnd = (int)(GAMEWORLD->getCamera()->y + GAMEWORLD->getCamera()->height) / tileSize;

	if (rowBegin < 0 || columnBegin < 0 || rowEnd >= row || columnEnd >= column || rowBegin>rowEnd || columnBegin>columnEnd)
		return;

	for (int i = rowBegin; i <= rowEnd; i++) {
		for (int j = columnBegin; j <= columnEnd; j++) {
			SPRITES->Get((int)matrixMap[i][j] + offset)->Draw((int)x + j * tileSize - (int)GAMEWORLD->getCamera()->x,
				(int)y + i * tileSize - (int)GAMEWORLD->getCamera()->y);
		}
	}


}

bool BackgroundMap::InitMap(const char * filePath, int offset)
{
	this->offset = offset;
	ifstream infile;
	try {


		//SPRITES->Add(11, 8, 224, 79, 253, TEXTURES->Get(1));
		// mo mot file trong che do read.

		infile.open(filePath);
		if (!infile) {
			//MessageBox(WINDOW->getWindowHandler(), "failed to read Sprite data", "Error", MB_ICONERROR);
			return false;
		}

		if (!infile) {
			infile.close();
			return false;
		}

		infile >> row;
		infile >> column;
		OutputDebugString((std::to_string(row) + "\n ").c_str());
		OutputDebugString((std::to_string(column) + "\n ").c_str());
		matrixMap = new int*[row];

		for (int i = 0; i < row; i++) {
			matrixMap[i] = new int[column];
			for (int j = 0; j < column; j++) {
				infile >> matrixMap[i][j];
				OutputDebugString((std::to_string(matrixMap[i][j]) + " ").c_str());
			}
		}

		// dong file da mo.
		infile.close();
	}
	catch (...) {
		infile.close();
		return false;
	}
	return true;
}

BackgroundMap::BackgroundMap()
{
	tileSize = TILE_SIZE;
	x = 0;
	y = 0;
}


BackgroundMap::~BackgroundMap()
{
	for (int i = 0; i < row; ++i) {
		delete[] matrixMap[i];
	}
	delete[] matrixMap;
}
