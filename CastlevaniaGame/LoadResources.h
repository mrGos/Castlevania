#pragma once
#include "ReadFilesHelper.h"

using namespace std;

class LoadResources
{
private:
	static LoadResources* _instance;
	LoadResources();

public:

	static LoadResources* getInstance();

	void InitResources();

	bool LoadTextures();
	bool LoadSprites();
	bool LoadAnimations();
	bool LoadObject(const char* filePath);

	~LoadResources();
};

