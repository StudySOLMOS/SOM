#include "stdafx.h"
#include "Entity.h"
#include "Mesh.h"

CEntity::CEntity() 
	: m_matLocal()
{
	D3DXMatrixIdentity(&m_matLocal);
}

CEntity::~CEntity(void)
{
}

void CEntity::Pulse()
{
	D3DXMatrixIdentity(&m_matLocal);
	//물체를 Y축을 기준으로 회전시키게 된다.
	//Every 0.5 Seconds Object will be Rotation
	D3DXMatrixRotationYawPitchRoll(&matWorld, GetTickCount()/500.0f, GetTickCount()/500.0f, GetTickCount()/500.0f);

}

bool CEntity::SetTextureFile(LPDIRECT3DTEXTURE9 pTexture, char* strFilename)
{
	if(!pTexture)
	{
		return false;
	}

	m_pTexture = pTexture;

	if(FAILED(D3DXCreateTextureFromFileA(m_pDevice, strFilename,&m_pTexture)))
	{
		MessageBox(NULL, "Could not find Smile.bmp", "Study.exe", MB_OK);
		return false;
	}

	if(m_pTexture)
	{
		m_pDevice->SetTexture(0, m_pTexture);
	}

	return true;
}