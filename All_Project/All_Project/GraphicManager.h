#pragma once
#include "stdafx.h"

class CGraphicManager
{
public:
	CGraphicManager(void);
	virtual ~CGraphicManager(void);

public:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	LPDIRECT3DTEXTURE9 m_pTexture;

public:
	bool Initialize();
	bool InitializeVertexBuffer();
	bool InitializeIndexBuffer();
	void Pulse();
	void PreRender();
	void Render();
	void PostRender();
	void Release();

public:
	void SetupLights();
	void SetupMatrix();
	void InitializeGeoMetry();
};
