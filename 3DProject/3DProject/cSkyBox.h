#pragma once
#include "cGameObject.h"

class cSkyBox :
	public cGameObject
{
public:
	cSkyBox(int number);
	virtual ~cSkyBox();

	void Render();
	void Update();
private:
	void Setup();
	void Setup2();

private:
	LPDIRECT3DVERTEXBUFFER9			m_pVertexBuffer;
	LPDIRECT3DTEXTURE9				m_pTexture[6];
	std::vector<ST_PT_VERTEX>		m_vecVertex;
};