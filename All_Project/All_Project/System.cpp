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
	m_bIsActive = true;
	m_pGraphicManager = new CGraphicManager;
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
	wc.lpszClassName ="D3D Tutorial";
	wc.hIconSm = NULL;

	RegisterClassEx( &wc );

	/// ������ Ŭ���� ���
	/// ������ ũ��
	m_iScreenWidth = 1024;
	m_iScreenHeigth = 768;

	/// ������ ����
	m_hWnd = CreateWindow( "D3D Tutorial", "D3D Tutorial : Direct3D Class",
		WS_OVERLAPPEDWINDOW, 0, 0, m_iScreenWidth, m_iScreenHeigth,
		GetDesktopWindow(), NULL, wc.hInstance, NULL );

	if(NULL==(m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return false;
	}

	//����̽� ������ �ϱ����� �ʱ⼳��.
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
	d3dpp.BackBufferFormat = d3dDisplayMode.Format;
	d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;


	//����̽� ����
	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp, &m_pGraphicManager->m_pD3DDevice)))
	{
		return false;
	}

	m_pD3D->Release();

	return true;
}

void CSystem::Pulse()
{
	/// Direct3D �ʱ�ȭ
	if( SUCCEEDED( m_pGraphicManager->Initialize() ))
	{
		/// �������� �ʱ�ȭ
		if( SUCCEEDED( m_pGraphicManager->InitializeVertexBuffer()  ))
		{
			/// �ε������� �ʱ�ȭ
			if( SUCCEEDED( m_pGraphicManager->InitializeIndexBuffer() ) )
			{
				/// ������ ���
				ShowWindow( m_hWnd, SW_SHOWDEFAULT );
				UpdateWindow( m_hWnd );

				/// �޽��� ����
				MSG msg;
				ZeroMemory( &msg, sizeof(msg) );
				while( msg.message!=WM_QUIT )
				{
					/// �޽���ť�� �޽����� ������ �޽��� ó��
					if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
					{
						TranslateMessage( &msg );
						DispatchMessage( &msg );
					}

					else if(m_bIsActive)
					{
						/// ó���� �޽����� ������ Render()�Լ� ȣ��
						UpdateFrame();
					}

					else
					{
						WaitMessage();
					}
				}
			}
		}
	}

	/// ��ϵ� Ŭ���� �Ұ�
	UnregisterClass( "D3D Tutorial", wc.hInstance );
}

void CSystem::Render()
{
}

void CSystem::Release()
{
	delete m_pGraphicManager;
}

void CSystem::UpdateFrame()
{
	m_pGraphicManager->PreRender();

	//���� ������ �ؾ� �ϴ� ��
	{
		m_pGraphicManager->Render();
	}

	m_pGraphicManager->PostRender();
}