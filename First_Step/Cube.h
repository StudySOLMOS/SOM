#pragma once
#include "Mesh.h"
#include "Entity.h"


class CCube :
	public CEntity
{
public:
	CCube(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CCube(void);

public:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	//D3DXMATRIX matWorld;

public:
	bool Initialize(float fSize);
	void Pulse();
	void Render();
	void Release();
};
