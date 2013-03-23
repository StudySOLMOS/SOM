#pragma once

#include "Cube.h"


class CGraphicManager
{
public:
	CGraphicManager(void);
	virtual ~CGraphicManager(void);

public:
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	CCube* m_Cube;

public:
	bool Initialize();
	void Pulse();
	void PreRender();
	void Render();
	void PostRender();
	void Release();

public:
	void GlobalLights();
	void SetupMatrix();
	void InitializeGeoMetry();
};
