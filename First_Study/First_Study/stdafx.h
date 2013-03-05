//Window, Direct Header
#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>

#include <d3dx9.h>
#include <stdlib.h>

//Lib
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//사용자 설정 함수,구조체,Define
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

struct CUSTOMVERTEX
{
	float m_x, m_y, m_z;
	float nx, ny, nz; 
	//DWORD color;
	float tu, tv;
};

struct CUSTOMINDEX
{
	DWORD m_First, m_Second, m_Third;
};
