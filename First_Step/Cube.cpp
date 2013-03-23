#include "stdafx.h"
#include "Cube.h"

CCube::CCube(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;
}

CCube::~CCube(void)
{
	delete m_pDevice;
}

bool CCube::Initialize(float fSize)
{
	if(!SetTextureFile(m_pTexture, "Smile.bmp"))
	{
		SetTextureFile(m_pTexture, "..\\Smile.bmp");
	}

	if(FAILED(m_pDevice->CreateVertexBuffer(24*sizeof(VERTEX), 0, VERTEX::FVF, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL)))
	{
		return false;
	}

	VERTEX Vertices[] = 
	{
		{ -fSize , fSize , -fSize , 0 , 1 , 0 , 0 , 0}, //0 0
		{ fSize , fSize , -fSize , 0 , 1 , 0 , 0 , 1},//1 1
		{ fSize , fSize , fSize , 0 , 1 , 0 , 1 , 1},//2 2
		{ -fSize , fSize , fSize , 0 , 1 , 0 , 1 , 0},//3 3

		{ -fSize , fSize , fSize , 0 , 0 , 1 , 0 , 0},//3 4
		{ fSize , fSize , fSize , 0 , 0 , 1 , 0 , 1},//2 5
		{ fSize , -fSize , fSize , 0 , 0 , 1 , 1 , 1},//4 6
		{ -fSize , -fSize , fSize , 0 , 0 , 1 , 1 , 0},//5 7

		{ -fSize , fSize , -fSize , -1 , 0 , 0 , 0 , 0},//0 8
		{ -fSize , fSize , fSize , -1 , 0 , 0 , 0 , 1},//3 9
		{ -fSize , -fSize , fSize , -1 , 0 , 0 , 1 , 1},//5 10
		{ -fSize , -fSize , -fSize , -1 , 0 , 0 , 1 , 0},//6 11

		{ fSize , fSize , fSize , 1 , 0 , 0 , 0 , 0},//2 12
		{ fSize , fSize , -fSize , 1 , 0 , 0 , 0 , 1},//1 13
		{ fSize , -fSize , -fSize , 1 , 0 , 0 , 1 , 1},//7 14
		{ fSize , -fSize , fSize , 1 , 0 , 0 , 1 , 0},//4 15

		{ fSize , fSize , -fSize , 0 , 0 , -1 , 0 , 0},//1 16
		{ -fSize , fSize , -fSize ,0 , 0 , -1 , 0 , 1},//0 17
		{ -fSize , -fSize , -fSize , 0 , 0 , -1 , 1 , 1},//6 18
		{ fSize , -fSize , -fSize ,0 , 0 , -1 , 1 , 0},//7 19

		{ fSize , -fSize , -fSize , 0 , -1 , 0 , 0 , 0},//7 20
		{ -fSize , -fSize , -fSize , 0 , -1 , 0 , 0 , 1},//6 21
		{ -fSize , -fSize , fSize , 0 , -1 , 0 , 1 , 1},//5 22
		{ fSize , -fSize , fSize , 0 , -1 , 0 , 1 , 0}//4 23
	};

	//정점버퍼를 값으로 채운다
	//정정버퍼의 Lock()함수를 호출하여 포인터를 얻어온다.
	void* pVertices;

	if(FAILED(m_pVertexBuffer->Lock(0, sizeof(Vertices),(void**)&pVertices,0)))
	{
		return false;
	}

	memcpy(pVertices, Vertices, sizeof(Vertices));

	//UnLock()함수를 호출하여 포인터로부터의 접근을 막는다.
	m_pVertexBuffer->Unlock();

	//인덱스 버퍼 생성
	//D3DFMT_INDEX32은 인덱스의 단위가 32비트라는 것.
	//CUSTOMINDEX구조체에서 DWORD형으로 선언하였으므로, D3DFMT_INDEX32을 사용한다.
	if(FAILED(m_pDevice->CreateIndexBuffer(12* sizeof(INDEX), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pIndexBuffer, NULL)))
	{
		return false;
	}

	INDEX	Index[] =
	{
		{ 0 , 3 , 1 },
		{ 1 , 3 , 2 },

		{ 4 , 7 , 5 },
		{ 5 , 7 , 6 },

		{ 8 , 11 , 9 },
		{ 9 , 11 , 10 },

		{ 12 , 15 , 13 },
		{ 13 , 15 , 14 },

		{ 16 , 19 , 17 },
		{ 17 , 19 , 18 },

		{ 20 , 23 , 21 },
		{ 21 , 23 , 22 },
	};


	void* pIndices;
	if(FAILED(m_pIndexBuffer->Lock(0, sizeof(Index), (void**)&pIndices,0)))
	{
		return false;
	}

	memcpy(pIndices, Index, sizeof(Index));

	m_pIndexBuffer->Unlock();
	return true;
}

void CCube::Pulse()
{
	D3DXMatrixIdentity(&m_matLocal);
	//물체를 Y축을 기준으로 회전시키게 된다.
	//Every 0.5 Seconds Object will be Rotation
	D3DXMatrixRotationYawPitchRoll(&m_matLocal, GetTickCount()/500.0f, GetTickCount()/500.0f, GetTickCount()/500.0f);
}

void CCube::Render()
{
	m_pDevice->SetMaterial(&m_Material);
	m_pDevice->SetTransform(D3DTS_WORLD, &m_matLocal);
	m_pDevice->SetStreamSource(0, m_pVertexBuffer, 0 , sizeof(VERTEX));
	m_pDevice->SetFVF(VERTEX::FVF);
	m_pDevice->SetIndices(m_pIndexBuffer);
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
}

void CCube::Release()
{
	if(m_pIndexBuffer != NULL)
	{
		m_pIndexBuffer->Release();
	}

	if(m_pVertexBuffer != NULL)
	{
		m_pVertexBuffer->Release();
	}

	if(m_pDevice != NULL)
	{
		m_pDevice->Release();
	}
}