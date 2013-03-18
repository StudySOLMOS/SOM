#pragma once
#include "MeshBuffer.h"

class CMeshBuffer;


class CMesh
{
public:
	CMesh(void);
	~CMesh(void);

public:
	bool Initialize();
	void Pulse();
	void Render();
	void Release();
};