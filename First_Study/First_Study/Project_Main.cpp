#include "stdafx.h"
#include "System.h"

int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	CSystem* pSystem = new CSystem;

	if(!pSystem->Initialize())
	{
		return -1;
	}

	pSystem->Pulse();

	pSystem->Release();

	delete pSystem;
	return 0;
}