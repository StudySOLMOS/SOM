#include "stdafx.h"
#include "Mesh.h"

CMesh::CMesh(void)
{

}

CMesh::~CMesh(void)
{

}

bool CMesh::Initialize()
{
	return true;
}

void CMesh::Pulse()
{

}

void CMesh::Render()
{

}

void CMesh::Release()
{
	if(m_pDevice != NULL)
	{
		m_pDevice->Release();
	}
}