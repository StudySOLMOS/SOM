//Window, Direct Header
#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

//사용자 설정 헤더

//사용자 설정 함수,구조체,Define
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)
struct CUSTOMVERTEX
{
	float m_x, m_y, m_z;
	DWORD color;
	float tu, tv;
};

struct CUSTOMINDEX
{
	WORD m_First, m_Second, m_Third;
};
