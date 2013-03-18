#include "stdafx.h"
#include "GraphicManager.h"

CGraphicManager::CGraphicManager(void)
{
	
}

CGraphicManager::~CGraphicManager(void)
{
}

bool CGraphicManager::Initialize()
{
	m_Cube = new CCube(m_pD3DDevice);
	m_Cube->Initialize(60.0f);


	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	return true;
}

void CGraphicManager::Pulse()
{
	m_Cube->Pulse();
}

void CGraphicManager::PreRender()
{
	//Screen  Clear
	m_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255,255,255), 1.0f, 0 );
	m_pD3DDevice->BeginScene();
}

void CGraphicManager::Render()
{
	GlobalLights();

	SetupMatrix();

	m_Cube->Render();

	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);					//첫번째 섞을 색은 텍스처 색
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);					//두번째 섞을 색은 정점 색
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
}

void CGraphicManager::PostRender()
{
	m_pD3DDevice->EndScene();
	/// 후면버퍼를 보이는 화면으로
	m_pD3DDevice->Present( NULL, NULL, NULL, NULL );
}

void CGraphicManager::Release()
{
	if(m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
	}
}

void CGraphicManager::SetupMatrix()
{
	//World Matrix, View Matrix, Projection Matrix 순으로 설정을 하여야 한다.
	//View Matrix
	D3DXVECTOR3 vEyePt(0.0f, -300.0f, -300.0f);
	D3DXVECTOR3 vLookAtPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);

	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookAtPt, &vUpVector);
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	//Projection Matrix
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.0f, 1.0f, 1000.0f);
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void CGraphicManager::GlobalLights()
{
	//재질 설정
	//재질은 디바이스에 단 하나만 설정 될수 있다.
	D3DMATERIAL9 Material;

	ZeroMemory(&Material, sizeof(D3DMATERIAL9));
	Material.Diffuse.r = Material.Ambient.r = 1.0f;
	Material.Diffuse.g = Material.Ambient.g = 1.0f;
	Material.Diffuse.b = Material.Ambient.b = 0.0f;
	Material.Diffuse.a = Material.Ambient.a = 1.0f;
	m_pD3DDevice->SetMaterial(&Material);


	D3DXVECTOR3 vecDir;	//빛의 방향
	D3DLIGHT9 light;		//광원구조체

	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;		//광원의 종류(점 광원, 방향성 광원, 스포트라이트)
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	vecDir = D3DXVECTOR3(0, 0, 1);		//광원의 방향
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);							//광원의 방향을 단위벡터로 만듬
	light.Range = 1000.0f;																				//광원이 다다를 수 있는 최대 거리
	m_pD3DDevice->SetLight(0, &light);																//디바이스에 0번 광원 설치
	m_pD3DDevice->LightEnable(0, TRUE);															//0번 광원을 켠다
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);									//광원 설정을 켠다
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}