#pragma once
#include "stdafx.h"

class CEntity
{
public:
	CEntity(void);
	virtual ~CEntity(void);

public:
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXMATRIX m_matLocal;
	D3DMATERIAL9 m_Material;

public:
	bool SetTextureFile(LPDIRECT3DTEXTURE9 pTexture, char* strFilename);
};