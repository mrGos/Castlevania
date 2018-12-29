#include "CSprites.h"


CSprites* CSprites::_instance = 0;
CSprites::CSprites()
{
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

CSprites * CSprites::getInstance()
{
	if (_instance == 0)
		_instance = new CSprites();
	return _instance;
}

CSprites::~CSprites()
{
	delete this;
}




CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

//void CSprite::Draw(float x, float y, int alpha)
//{
//	GRAPHICS->Draw(x, y, texture, left, top, right, bottom, alpha);
//}

void CSprite::Draw(float x, float y, int alpha, bool isFlip)
{
	GRAPHICS->Draw(x, y, isFlip, texture, left, top, right, bottom, alpha);
}



