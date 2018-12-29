#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "CGraphics.h"
#include "AppConfiguration.h"

class CSprite {
private:
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public:
	int getLeft() { return this->left; }
	int getTop() { return this->top; }
	int getRight() { return this->right; }
	int getBottom() { return this->bottom; }
	int getWidth() { return (right - left); }
	int getHeight() { return (bottom - top); }

	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y, int alpha = 255, bool isFlip = false);

	/*void DrawWithFlipX(float x, float y, bool isFlip = false, int alpha = 255);*/
};
typedef CSprite * LPSPRITE;

class CSprites
{
private:
	static CSprites * _instance;
	std::unordered_map<int, LPSPRITE> sprites;

	CSprites();
public:

	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);

	static CSprites * getInstance();
	~CSprites();
};

