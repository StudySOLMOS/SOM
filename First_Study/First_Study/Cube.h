#pragma once

class CMesh;

class CCube
{
public:
	CCube(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CCube(void);

public:
	LPDIRECT3DDEVICE9 m_pDevice;

public:
	bool Initialize(float fSize);
	void Pulse();
	void Render();
	void Release();
};
