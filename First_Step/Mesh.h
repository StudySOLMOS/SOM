#pragma once
#include "MeshBuffer.h"

class CMeshBuffer;

struct VERTEX
{
	float m_x, m_y, m_z;
	float nx, ny, nz; 
	float tu, tv;

	enum
	{
		FVF =  (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)
	};
};

struct INDEX
{
	DWORD m_First, m_Second, m_Third;
};

class CMesh
{
public:
	CMesh(void);
	~CMesh(void);

public:
	LPDIRECT3DDEVICE9 m_pDevice;

public:
	bool Initialize();
	void Pulse();
	void Render();
	void Release();
};