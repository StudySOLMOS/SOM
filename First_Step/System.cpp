#include "stdafx.h"
#include "System.h"

CSystem::CSystem(void)
{
}

CSystem::~CSystem(void)
{
} 

LRESULT CALLBACK MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

bool CSystem::Initialize()
{
	//Class Initialize
	m_bIsActive = true;
	m_pGraphicManager = new CGraphicManager;

	//Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = (WNDPROC)MsgProc;
	wc.cbClsExtra = 0L;
	wc.cbWndExtra = 0L;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName ="Study";
	wc.hIconSm = NULL;

	RegisterClassEx( &wc );

	/// 윈도우 크기
	m_iScreenWidth = 500;
	m_iScreenHeigth = 460;

	/// 윈도우 생성
	m_hWnd = CreateWindow( wc.lpszClassName, "SOM : First Study",	WS_OVERLAPPEDWINDOW, 0, 0, m_iScreenWidth, m_iScreenHeigth, GetDesktopWindow(), NULL, wc.hInstance, NULL );

	if(!m_hWnd)
	{
		MessageBox(NULL, "Could not find hWnd", "Study.exe", MB_OK);
		return false;
	}

	if(NULL==(m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return false;
	}

	//디바이스 생성을 하기위한 초기설정.
	D3DPRESENT_PARAMETERS d3dpp;

	D3DDISPLAYMODE d3dDisplayMode;

	m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3dDisplayMode);

	D3DCAPS9 d3dCaps;

	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,&d3dCaps);

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = true;
	d3dpp.hDeviceWindow = m_hWnd;
	d3dpp.SwapEffect =  D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = d3dDisplayMode.Width;
	d3dpp.BackBufferHeight = d3dDisplayMode.Height;
	d3dpp.BackBufferFormat = d3dDisplayMode.Format;//D3DFMT_D16;
	d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;


	//디바이스 생성
	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp, &m_pGraphicManager->m_pD3DDevice)))
	{
		return false;
	}

	if(m_pD3D!=NULL)
	{
		m_pD3D->Release();
	}

	return true;
}

void CSystem::Pulse()
{
	/// Direct3D 초기화
	if( SUCCEEDED( m_pGraphicManager->Initialize() ))
	{
		/// 윈도우 출력
		ShowWindow( m_hWnd, SW_SHOWDEFAULT );
		UpdateWindow( m_hWnd );

		/// 메시지 루프
		MSG msg;
		ZeroMemory( &msg, sizeof(msg) );
		while( msg.message!=WM_QUIT )
		{
			/// 메시지큐에 메시지가 있으면 메시지 처리
			if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}

			else if(m_bIsActive)
			{
				/// 처리할 메시지가 없으면 Render()함수 호출
				UpdateFrame();
			}

			else
			{
				WaitMessage();
			}
		}
	}

	/// 등록된 클래스 소거
	UnregisterClass( "Study", wc.hInstance );
}

void CSystem::Render()
{
	m_pGraphicManager->PreRender();

	//실제 렌더링 해야 하는 곳
	{
		m_pGraphicManager->Render();
	}

	m_pGraphicManager->PostRender();
}

void CSystem::Release()
{
	m_pGraphicManager->Release();
	delete m_pGraphicManager;
}

void CSystem::UpdateFrame()
{
	m_pGraphicManager->Pulse();
	Render();
}