#pragma once

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

class CCube;

class CMeshBuffer
{
public:
	CMeshBuffer(void);
	~CMeshBuffer(void);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	LPDIRECT3DTEXTURE9 m_pTexture;

public:
	UINT m_pVertices;
	UINT m_pIndices;

public:
	void Render(LPDIRECT3DDEVICE9 pDevice);
};

