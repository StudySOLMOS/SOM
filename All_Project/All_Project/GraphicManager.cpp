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
	//D3DFMT_INDEX16은 인덱스의 단위가 16비트라는 것.
	//CUSTOMINDEX구조체에서 WORD형으로 선언하였으므로, D3DFMT_INDEX16을 사용한다.
	if(FAILED(m_pD3DDevice->CreateIndexBuffer(12* sizeof(CUSTOMINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuffer, NULL)))
	{
		return false;
	}

	CUSTOMINDEX	Index[] =
	{
		{ 0, 1, 2 }, { 0, 2, 3 },	/// 윗면
		{ 4, 6, 5 }, { 4, 7, 6 },	/// 아랫면
		{ 0, 3, 7 }, { 0, 7, 4 },	/// 왼쪽면
		{ 1, 5, 6 }, { 1, 6, 2 },	/// 오른면
		{ 3, 2, 6 }, { 3, 6, 7 },	/// 앞면
		{ 0, 4, 5 }, { 0, 5, 1 }		/// 뒷면
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
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);					//첫번째 섞을 색은 텍스처 색
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);					//두번째 섞을 색은 정점 색
	//m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
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

	//if(m_pD3D != NULL)
	//{
	//	m_pD3D->Release();
	//}
}

void CGraphicManager::SetupMatrix()
{
	//World Matrix, View Matrix, Projection Matrix 순으로 설정을 하여야 한다.

	//World Matrix
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	//물체를 Y축을 기준으로 회전시키게 된다.
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

	//vecDir = D3DXVECTOR3(cosf(timeGetTime()/350.0f), 1.0f, sinf(timeGetTime()/350.0f));		//광원의 방향
	vecDir = D3DXVECTOR3(0, 0, 1);		//광원의 방향
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);							//광원의 방향을 단위벡터로 만듬
	light.Range = 10.0f;																				//광원이 다다를 수 있는 최대 거리
	m_pD3DDevice->SetLight(0, &light);																//디바이스에 0번 광원 설치
	m_pD3DDevice->LightEnable(0, TRUE);															//0번 광원을 켠다
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);									//광원 설정을 켠다
	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}