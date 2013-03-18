#pragma once

class CMesh;

class CEntity
{
public:
	CEntity(void);
	virtual ~CEntity(void);

public:
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DMATRIX m_matLocal;

public:
	virtual bool Initialize()=0;
	virtual void Pulse()=0;
	virtual void Render()=0;
	virtual void Release()=0;

public:
	bool SetTextureFile(LPDIRECT3DTEXTURE9 pTexture, char* strFilename);
};