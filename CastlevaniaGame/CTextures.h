#pragma once
#include <unordered_map>
#include <d3dx9.h>
#include "AppConfiguration.h"
#include "CGraphics.h"

class CTextures
{
private:
	static CTextures* _instance;
	std::unordered_map<int, LPDIRECT3DTEXTURE9> textures;

	CTextures();
public:
	static CTextures * getInstance();

	void Add(int id, LPCSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);

};

