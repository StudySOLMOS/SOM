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
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);					//ù��° ���� ���� �ؽ�ó ��
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);					//�ι�° ���� ���� ���� ��
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
}

void CGraphicManager::PostRender()
{
	m_pD3DDevice->EndScene();
	/// �ĸ���۸� ���̴� ȭ������
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
	//World Matrix, View Matrix, Projection Matrix ������ ������ �Ͽ��� �Ѵ�.
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
	//���� ����
	//������ ����̽��� �� �ϳ��� ���� �ɼ� �ִ�.
	D3DMATERIAL9 Material;

	ZeroMemory(&Material, sizeof(D3DMATERIAL9));
	Material.Diffuse.r = Material.Ambient.r = 1.0f;
	Material.Diffuse.g = Material.Ambient.g = 1.0f;
	Material.Diffuse.b = Material.Ambient.b = 0.0f;
	Material.Diffuse.a = Material.Ambient.a = 1.0f;
	m_pD3DDevice->SetMaterial(&Material);


	D3DXVECTOR3 vecDir;	//���� ����
	D3DLIGHT9 light;		//��������ü

	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;		//������ ����(�� ����, ���⼺ ����, ����Ʈ����Ʈ)
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	vecDir = D3DXVECTOR3(0, 0, 1);		//������ ����
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);							//������ ������ �������ͷ� ����
	light.Range = 1000.0f;																				//������ �ٴٸ� �� �ִ� �ִ� �Ÿ�
	m_pD3DDevice->SetLight(0, &light);																//����̽��� 0�� ���� ��ġ
	m_pD3DDevice->LightEnable(0, TRUE);															//0�� ������ �Ҵ�
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);									//���� ������ �Ҵ�
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}