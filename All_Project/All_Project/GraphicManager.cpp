#include "GraphicManager.h"

CGraphicManager::CGraphicManager(void)
{
}

CGraphicManager::~CGraphicManager(void)
{
}

bool CGraphicManager::Initialize()
{
	if(FAILED(D3DXCreateTextureFromFileA(m_pD3DDevice, "HighSchool.bmp",&m_pTexture)))
	{
		if(FAILED(D3DXCreateTextureFromFileA(m_pD3DDevice, "..\\HighSchool.bmp",&m_pTexture)))
		{
			MessageBox(NULL, "Could not find HighSchool.bmp", "Study.exe", MB_OK);
			return false;
		}
	}

	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	if(FAILED(m_pD3DDevice->CreateVertexBuffer(8*sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL)))
	{
		return false;
	}

	CUSTOMVERTEX Vertices[] = 
	{
		{ -1,  1,  1 , 0xffff0000 },		/// v0
		{  1,  1,  1 , 0xff00ff00 },		/// v1
		{  1,  1, -1 , 0xff0000ff },		/// v2
		{ -1,  1, -1 , 0xffffff00 },			/// v3

		{ -1, -1,  1 , 0xff00ffff },			/// v4
		{  1, -1,  1 , 0xffff00ff },			/// v5
		{  1, -1, -1 , 0xff000000 },		/// v6
		{ -1, -1, -1 , 0xffffffff },			/// v7
	};

	//�������۸� ������ ä���
	//���������� Lock()�Լ��� ȣ���Ͽ� �����͸� ���´�.
	void* pVertices;

	if(FAILED(m_pVertexBuffer->Lock(0, sizeof(Vertices),(void**)&pVertices,0)))
	{
		return false;
	}

	memcpy(pVertices, Vertices, sizeof(Vertices));

	//UnLock()�Լ��� ȣ���Ͽ� �����ͷκ����� ������ ���´�.
	m_pVertexBuffer->Unlock();

	//�ε��� ���� ����
	//D3DFMT_INDEX16�� �ε����� ������ 16��Ʈ��� ��.
	//CUSTOMINDEX����ü���� WORD������ �����Ͽ����Ƿ�, D3DFMT_INDEX16�� ����Ѵ�.
	if(FAILED(m_pD3DDevice->CreateIndexBuffer(12* sizeof(CUSTOMINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuffer, NULL)))
	{
		return false;
	}

	CUSTOMINDEX	Index[] =
	{
		{ 0, 1, 2 }, { 0, 2, 3 },	/// ����
		{ 4, 6, 5 }, { 4, 7, 6 },	/// �Ʒ���
		{ 0, 3, 7 }, { 0, 7, 4 },	/// ���ʸ�
		{ 1, 5, 6 }, { 1, 6, 2 },	/// ������
		{ 3, 2, 6 }, { 3, 6, 7 },	/// �ո�
		{ 0, 4, 5 }, { 0, 5, 1 }		/// �޸�
	};


	void* pIndices;
	if(FAILED(m_pIndexBuffer->Lock(0, sizeof(Index), (void**)&pIndices,0)))
	{
		return false;
	}

	memcpy(pIndices, Index, sizeof(Index));

	m_pIndexBuffer->Unlock();


	//m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	return true;
}

void CGraphicManager::Pulse()
{

}

void CGraphicManager::PreRender()
{
	//Screen  Clear
	m_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );
	m_pD3DDevice->BeginScene();
}

void CGraphicManager::Render()
{
	SetupLights();

	SetupMatrix();

	if(m_pTexture)
	{
		m_pD3DDevice->SetTexture(0, m_pTexture);
	}

	m_pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0 , sizeof(CUSTOMVERTEX));
	m_pD3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pD3DDevice->SetIndices(m_pIndexBuffer);
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);					//ù��° ���� ���� �ؽ�ó ��
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);					//�ι�° ���� ���� ���� ��
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
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

	//if(m_pD3D != NULL)
	//{
	//	m_pD3D->Release();
	//}
}

void CGraphicManager::SetupMatrix()
{
	//World Matrix, View Matrix, Projection Matrix ������ ������ �Ͽ��� �Ѵ�.

	//World Matrix
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	//��ü�� Y���� �������� ȸ����Ű�� �ȴ�.
	//Every 0.5 Seconds Object will be Rotation
	D3DXMatrixRotationY(&matWorld, GetTickCount()/500.0f);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	//View Matrix
	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -10.0f);
	D3DXVECTOR3 vLookAtPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVector(0.0f, 1.0f, 0.0f);

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookAtPt, &vUpVector);
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	//Projection Matrix
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f);
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void CGraphicManager::SetupLights()
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

	//vecDir = D3DXVECTOR3(cosf(timeGetTime()/350.0f), 1.0f, sinf(timeGetTime()/350.0f));		//������ ����
	vecDir = D3DXVECTOR3(0, 0, 1);		//������ ����
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);							//������ ������ �������ͷ� ����
	light.Range = 10.0f;																				//������ �ٴٸ� �� �ִ� �ִ� �Ÿ�
	m_pD3DDevice->SetLight(0, &light);																//����̽��� 0�� ���� ��ġ
	m_pD3DDevice->LightEnable(0, TRUE);															//0�� ������ �Ҵ�
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);									//���� ������ �Ҵ�
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}