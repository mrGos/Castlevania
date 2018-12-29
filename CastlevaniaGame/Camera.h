#pragma once
#include "CGameObject.h"

class Camera :public CGameObject
{

	static Camera * _instance;
	Camera();
public:
	bool isLocked = false;
	static Camera * getInstance();

	float leftCornerBlock = 0;
	float rightCornerBlock = 0;

	Camera(float x, float y, float wView, float hView);

	void Lock() { isLocked = true; }
	void UnLock() { isLocked = false; }

	void SetCornerBlock(float l, float r);

	void Render() {}
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);


	~Camera();
};

typedef Camera* LPCAMERA;