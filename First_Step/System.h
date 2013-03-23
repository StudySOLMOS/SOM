#pragma once
#include "GraphicManager.h"

class CSystem
{
public:
	CSystem(void);
	~CSystem(void);

public:
	LPDIRECT3D9 m_pD3D;

public:
	WNDCLASSEX wc;
	bool m_bIsActive;
	HWND m_hWnd;
	int m_iScreenWidth;
	int m_iScreenHeigth;

public:
	CGraphicManager* m_pGraphicManager;

public:
	bool Initialize();
	void Pulse();
	void Render();
	void Release();

public:
	void UpdateFrame();
};
