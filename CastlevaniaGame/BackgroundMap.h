#pragma once
#include <fstream>
#include "CDObject.h"

using namespace std;
class BackgroundMap : public CDObject
{
	int **matrixMap;
	int row, column;

	int tileSize;
	int offset = 0;

public:

	void Render();
	bool InitMap(const char * filePath, int offset = 0);

	BackgroundMap();
	~BackgroundMap();
};

typedef BackgroundMap* LPBACKGROUNDMAP;