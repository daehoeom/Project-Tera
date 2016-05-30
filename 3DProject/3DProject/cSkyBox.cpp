#include "stdafx.h"
#include "cSkyBox.h"


cSkyBox::cSkyBox()
	: m_pTexture(NULL)
	, m_pVertexBuffer(NULL)
{

}


cSkyBox::~cSkyBox()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pVertexBuffer);
}

void cSkyBox::Setup()
{
	g_pD3DDevice->CreateVertexBuffer(36 * sizeof(ST_PT_VERTEX), D3DUSAGE_WRITEONLY,
		ST_PT_VERTEX::FVF, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);

	D3DXVECTOR3 vertex[8];
	vertex[0] = D3DXVECTOR3(-100.0f, -100.0f, -100.0f);
	vertex[1] = D3DXVECTOR3(-100.0f, -100.0f, 100.0f);
	vertex[2] = D3DXVECTOR3(100.0f, -100.0f, 100.0f);
	vertex[3] = D3DXVECTOR3(100.0f, -100.0f, -100.0f);
	vertex[4] = D3DXVECTOR3(-100.0f, 100.0f, -100.0f);
	vertex[5] = D3DXVECTOR3(-100.0f, 100.0f, 100.0f);
	vertex[6] = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
	vertex[7] = D3DXVECTOR3(100.0f, 100.0f, -100.0f);

	float uBase = 0.25f;
	float vBase = 0.34f;



	//아래
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[0], D3DXVECTOR2(uBase * 1, vBase * 3)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[1], D3DXVECTOR2(uBase * 1, vBase * 2)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[2], D3DXVECTOR2(uBase * 2, vBase * 2)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[0], D3DXVECTOR2(uBase * 1, vBase * 2)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[2], D3DXVECTOR2(uBase * 2, vBase * 3)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[3], D3DXVECTOR2(uBase * 2, vBase * 2)));

	//왼
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[4], D3DXVECTOR2(uBase * 1, vBase * 1)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[5], D3DXVECTOR2(uBase * 0, vBase * 1)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[1], D3DXVECTOR2(uBase * 0, vBase * 2)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[4], D3DXVECTOR2(uBase * 1, vBase * 1)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[1], D3DXVECTOR2(uBase * 0, vBase * 2)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[0], D3DXVECTOR2(uBase * 1, vBase * 2)));

	//위
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[7], D3DXVECTOR2(uBase * 2, vBase * 1)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[6], D3DXVECTOR2(uBase * 2, vBase * 0)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[5], D3DXVECTOR2(uBase * 1, vBase * 0)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[7], D3DXVECTOR2(uBase * 2, vBase * 1)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[5], D3DXVECTOR2(uBase * 1, vBase * 0)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[4], D3DXVECTOR2(uBase * 1, vBase * 1)));

	//오
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[3], D3DXVECTOR2(uBase * 2, vBase * 2)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[2], D3DXVECTOR2(uBase * 3, vBase * 2)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[6], D3DXVECTOR2(uBase * 3, vBase * 1)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[3], D3DXVECTOR2(uBase * 2, vBase * 2)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[6], D3DXVECTOR2(uBase * 3, vBase * 1)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[7], D3DXVECTOR2(uBase * 2, vBase * 1)));

	//뒤
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[1], D3DXVECTOR2(uBase * 4, vBase * 2)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[5], D3DXVECTOR2(uBase * 4, vBase * 1)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[6], D3DXVECTOR2(uBase * 3, vBase * 1)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[1], D3DXVECTOR2(uBase * 4, vBase * 2)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[6], D3DXVECTOR2(uBase * 3, vBase * 1)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[2], D3DXVECTOR2(uBase * 3, vBase * 2)));

	//앞
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[4], D3DXVECTOR2(uBase * 1, vBase * 1)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[0], D3DXVECTOR2(uBase * 1, vBase * 2)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[3], D3DXVECTOR2(uBase * 2, vBase * 2)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[4], D3DXVECTOR2(uBase * 1, vBase * 1)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[3], D3DXVECTOR2(uBase * 2, vBase * 2)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[7], D3DXVECTOR2(uBase * 2, vBase * 1)));

	ST_PT_VERTEX* vertices;
	m_pVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		vertices[i] = m_vecVertex[i];
	}

	m_pVertexBuffer->Unlock();

	D3DXCreateTextureFromFile(
		g_pD3DDevice,
		"./Sky.jpg",
		&m_pTexture);
}

void cSkyBox::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(ST_PT_VERTEX));
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_vecVertex.size());
}

void cSkyBox::Update()
{

}