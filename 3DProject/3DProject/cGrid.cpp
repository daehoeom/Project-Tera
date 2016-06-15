#include "StdAfx.h"
#include "cGrid.h"

cGrid::cGrid( int nLine /*= 30*/, float fInterval /*= 1.0f*/ )
	: m_pVB(NULL)
	, m_nNumLine(0)
{
	std::vector<ST_PC_VERTEX>	vecVertex;

	float fNumLine = nLine / 2;

	float fMax = fNumLine * fInterval;

	ST_PC_VERTEX v;

	for (int i = 1; i <= fNumLine; ++i)
	{
		if (i % 5 == 0)
		{
			v.c = D3DCOLOR_XRGB(255, 255, 255);
		}
		else
		{
			v.c = D3DCOLOR_XRGB(128, 128, 128);
		}
		v.p = D3DXVECTOR3(-fMax, 0, i * fInterval); vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i * fInterval); vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-fMax, 0, -i * fInterval); vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i * fInterval); vecVertex.push_back(v);

		v.p = D3DXVECTOR3(i * fInterval, 0, -fMax); vecVertex.push_back(v);
		v.p = D3DXVECTOR3(i * fInterval, 0, fMax); vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i * fInterval, 0, -fMax); vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, fMax); vecVertex.push_back(v);
	}

	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(-fMax, 0, 0); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0); vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, -fMax, 0); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, fMax, 0); vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0, 0, -fMax); vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax); vecVertex.push_back(v);

	m_nNumLine = vecVertex.size() / 2;

	g_pD3DDevice->CreateVertexBuffer(
		vecVertex.size() * sizeof(ST_PC_VERTEX),
		0,
		ST_PC_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		NULL);

	ST_PC_VERTEX* pV;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PC_VERTEX));
	m_pVB->Unlock();

}


cGrid::~cGrid(void)
{
	SAFE_RELEASE(m_pVB);
}

void cGrid::Render()
{
	g_pD3DDevice->SetTexture(0, 0);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16 matWorld;

	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_nNumLine);
}

void cGrid::Update( )
{
}
