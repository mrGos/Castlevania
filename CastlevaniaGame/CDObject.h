#pragma once
#include "AppConfiguration.h"
class CDObject
{
public:
	int id, tag;
	float x;
	float y;

	float gy = 0;

	float width, height;
public:
	float left() { return x; }
	float right() { return x + width; }
	float top() { return y; }
	float bottom() { return y + height; }
	float xCenter() { return x + width / 2; }
	float yCenter() { return y + height / 2; }

	CDObject();
	CDObject(float x, float y, float width, float height);
	~CDObject();
};

