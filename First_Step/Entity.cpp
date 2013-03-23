#include "stdafx.h"
#include "Entity.h"

CEntity::CEntity(void) : m_matLocal()
{
	D3DXMatrixIdentity(&m_matLocal);

	ZeroMemory(&m_Material, sizeof(D3DMATERIAL9));
	m_Material.Diffuse.r = 0.7f;
	m_Material.Diffuse.g = 0.7f;
	m_Material.Diffuse.b = 0.7f;
	m_Material.Ambient.r = 0.5f;
	m_Material.Ambient.g = 0.5f;
	m_Material.Ambient.b = 0.5f;
}

CEntity::~CEntity(void)
{
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
		MessageBox(NULL, "Could not find Texture File or Texture File name", "Study.exe", MB_OK);
		return false;
	}

	if(m_pTexture)
	{
		m_pDevice->SetTexture(0, m_pTexture);
	}

	return true;
}