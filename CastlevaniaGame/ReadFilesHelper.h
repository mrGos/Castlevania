#pragma once
#include <fstream>
#include "AppConfiguration.h"
#include "CTextures.h"
#include "CSprites.h"
#include "CAnimation.h"

using namespace std;

bool ReadAnimationFile(const char * filePath);
bool ReadSpriteFile(const char * filePath, int texId, int offset = 0);
bool ReadObject(const char * filePath);