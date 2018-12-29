#include "Camera.h"
#include "CSimon.h"


Camera* Camera::_instance = 0;
Camera::Camera(float x, float y, float wView, float hView)
{
	this->x = x;
	this->y = y;
	this->width = wView;
	this->height = hView;
	//SetCornerBlock(LEFT_CAMERA_INTRO_BLOCK, RIGHT_CAMERA_INTRO_BLOCK);
	SetCornerBlock(0, 5600);
}

void Camera::SetCornerBlock(float l, float r)
{
	leftCornerBlock = l;
	rightCornerBlock = r;
}

void Camera::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Camera::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	//if (this->x + width + SIMON->dx >= rightCornerBlock) {
	//	this->x = rightCornerBlock - width;
	//	Lock();
	//}
	//else if (this->x < leftCornerBlock) {
	//	x = leftCornerBlock;
	//	Lock();
	//}
	//else {
	//	UnLock();
	//}

	//if (!isLocked) {
	//	if ((SIMON->x + SIMON->dx) - this->x > CAMERA_UPDATE_RIGHT) this->x = SIMON->x - CAMERA_UPDATE_RIGHT;
	//	if ((SIMON->x + SIMON->dx) - this->x < CAMERA_UPDATE_LEFT) this->x = SIMON->x - CAMERA_UPDATE_LEFT;

	//	if (SIMON->y - y > CAMERA_UPDATE_BOTTOM) y = SIMON->y - CAMERA_UPDATE_BOTTOM;       //bottom
	//	else if (SIMON->y - y < CAMERA_UPDATE_TOP) y = SIMON->y - CAMERA_UPDATE_TOP;  //top
	//}
	if (!isLocked) {
		if ((SIMON->x + SIMON->dx < xCenter() && SIMON->dx < 0) || (SIMON->x + SIMON->dx > xCenter() && SIMON->dx > 0))
			dx = SIMON->dx;
		else
			dx = 0;

		if (x + dx < leftCornerBlock && dx < 0)
		{
			x = leftCornerBlock;
			dx = 0;
		}

		if (right() + dx > rightCornerBlock && dx > 0)
		{
			x = rightCornerBlock - width;
			dx = 0;
		}
		x += dx;
	}
}

Camera::Camera()
{
	//SetCornerBlock(0, 1504);
}

Camera * Camera::getInstance()
{
	if (_instance == 0)
		_instance = new Camera(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
	return _instance;
}


Camera::~Camera()
{
}
