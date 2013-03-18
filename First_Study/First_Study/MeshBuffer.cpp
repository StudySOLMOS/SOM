#include "stdafx.h"
#include "MeshBuffer.h"


CMeshBuffer::CMeshBuffer(void) 
	: m_pVertexBuffer(nullptr), m_pIndexBuffer(nullptr), m_pTexture(nullptr)
	, m_pVertices(0), m_pIndices(0)
{
}


CMeshBuffer::~CMeshBuffer(void)
{
	if (m_pVertexBuffer)
		m_pVertexBuffer->Release();

	if (m_pIndexBuffer)
		m_pIndexBuffer->Release();

	if (m_pTexture)
		m_pTexture->Release();
}


void CMeshBuffer::Render(LPDIRECT3DDEVICE9 pDevice)
{
	if(!pDevice)
	{
		return ;
	}

	if(!m_pVertexBuffer || !pDevice)
	{
		return ;
	}

	if(m_pTexture)
	{
		pDevice->SetTexture(0, m_pTexture);
	}

	pDevice->SetStreamSource(0, m_pVertexBuffer, 0 , sizeof(VERTEX));
	pDevice->SetFVF(VERTEX::FVF);
	pDevice->SetIndices(m_pIndexBuffer);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pVertices, 0, m_pIndices);
}