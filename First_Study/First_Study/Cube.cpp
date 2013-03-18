#include "stdafx.h"
#include "Mesh.h"
#include "Cube.h"

CCube::CCube(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
{
}

CCube::~CCube(void)
{
	delete m_pDevice;
}

bool CCube::Initialize(float fSize)
{
	if(!m_pDevice)
	{
		return nullptr;
	}

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
		{ -fSize , fSize , -fSize , 0 , 1 , 0 , 0 , 0},
		{ fSize , fSize , -fSize , 0 , 1 , 0 , 0 , 1},
		{ fSize , fSize , fSize , 0 , 1 , 0 , 1 , 1},
		{ -fSize , fSize , fSize , 0 , 1 , 0 , 1 , 0},

		{ -fSize , fSize , fSize , 0 , 0 , 1 , 0 , 0},
		{ fSize , fSize , fSize , 0 , 0 , 1 , 0 , 1},
		{ fSize , -fSize , fSize , 0 , 0 , 1 , 1 , 1},
		{ -fSize , -fSize , fSize , 0 , 0 , 1 , 1 , 0},

		{ -fSize , fSize , -fSize , -1 , 0 , 0 , 0 , 0},
		{ -fSize , fSize , fSize , -1 , 0 , 0 , 0 , 1},
		{ -fSize , -fSize , fSize , -1 , 0 , 0 , 1 , 1},
		{ -fSize , -fSize , -fSize , -1 , 0 , 0 , 1 , 0},

		{ fSize , fSize , fSize , 1 , 0 , 0 , 0 , 0},
		{ fSize , fSize , -fSize , 1 , 0 , 0 , 0 , 1},
		{ fSize , -fSize , -fSize , 1 , 0 , 0 , 1 , 1},
		{ fSize , -fSize , fSize , 1 , 0 , 0 , 1 , 0},

		{ fSize , fSize , -fSize , 0 , 0 , -1 , 0 , 0},
		{ -fSize , fSize , -fSize ,0 , 0 , -1 , 0 , 1},
		{ -fSize , -fSize , -fSize , 0 , 0 , -1 , 1 , 1},
		{ fSize , -fSize , -fSize ,0 , 0 , -1 , 1 , 0},

		{ fSize , -fSize , -fSize , 0 , -1 , 0 , 0 , 0},
		{ -fSize , -fSize , -fSize , 0 , -1 , 0 , 0 , 1},
		{ -fSize , -fSize , fSize , 0 , -1 , 0 , 1 , 1},
		{ fSize , -fSize , fSize , 0 , -1 , 0 , 1 , 0}
	};

	//�������۸� ������ ä���
	//���������� Lock()�Լ��� ȣ���Ͽ� �����͸� ���´�.

	if(FAILED(m_pVertexBuffer->Lock(0, sizeof(Vertices),(void**)&m_pVertices,0)))
	{
		return false;
	}

	memcpy(m_pVertices, Vertices, sizeof(Vertices));

	//UnLock()�Լ��� ȣ���Ͽ� �����ͷκ����� ������ ���´�.
	m_pVertexBuffer->Unlock();

	//�ε��� ���� ����
	//D3DFMT_INDEX32�� �ε����� ������ 32��Ʈ��� ��.
	//CUSTOMINDEX����ü���� DWORD������ �����Ͽ����Ƿ�, D3DFMT_INDEX32�� ����Ѵ�.
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

	if(FAILED(m_pIndexBuffer->Lock(0, sizeof(Index), (void**)&m_pIndices,0)))
	{
		return false;
	}

	memcpy(m_pIndices, Index, sizeof(Index));

	m_pIndexBuffer->Unlock();
	return true;
}

void CCube::Pulse()
{
	//World Matrix
	D3DXMatrixIdentity(&matWorld);
	//��ü�� Y���� �������� ȸ����Ű�� �ȴ�.
	//Every 0.5 Seconds Object will be Rotation
	D3DXMatrixRotationYawPitchRoll(&matWorld, GetTickCount()/500.0f, GetTickCount()/500.0f, GetTickCount()/500.0f);
}

void CCube::Render()
{
}

void CCube::Release()
{

}