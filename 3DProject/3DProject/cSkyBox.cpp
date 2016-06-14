#include "stdafx.h"
#include "cSkyBox.h"


cSkyBox::cSkyBox()
	: m_pVertexBuffer( nullptr )
{
	for ( size_t i = 0; i < _countof( m_pTexture ); ++i )
	{
		m_pTexture[i] = nullptr;
	}

	this->Setup( );
}


cSkyBox::~cSkyBox()
{
	for (size_t i = 0; i < _countof(m_pTexture); i++)
	{
		SAFE_RELEASE(m_pTexture[i]);
	}

	SAFE_RELEASE(m_pVertexBuffer);
}

void cSkyBox::Setup()
{
	g_pD3DDevice->CreateVertexBuffer(24 * sizeof(ST_PT_VERTEX), D3DUSAGE_WRITEONLY,
		ST_PT_VERTEX::FVF, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL);

	D3DXVECTOR3 vertex[8];
	vertex[0] = D3DXVECTOR3(-1024.f, -1024.f, -1024.f);
	vertex[1] = D3DXVECTOR3(-1024.f, -1024.f, 1024.0f);
	vertex[2] = D3DXVECTOR3(1024.0f, -1024.0f, 1024.0f);
	vertex[3] = D3DXVECTOR3(1024.0f, -1024.0f, -1024.0f);
	vertex[4] = D3DXVECTOR3(-1024.0f, 1024.0f, -1024.0f);
	vertex[5] = D3DXVECTOR3(-1024.0f, 1024.0f, 1024.0f);
	vertex[6] = D3DXVECTOR3(1024.0f, 1024.0f, 1024.0f);
	vertex[7] = D3DXVECTOR3(1024.0f, 1024.0f, -1024.0f);

	//아래
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[1], D3DXVECTOR2(0.f ,0.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[2], D3DXVECTOR2(1.f, 0.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[0], D3DXVECTOR2(0.f, 1.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[3], D3DXVECTOR2(1.f, 1.f)));

	//왼
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[4], D3DXVECTOR2(0.f, 0.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[5], D3DXVECTOR2(1.f, 0.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[0], D3DXVECTOR2(0.f, 1.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[1], D3DXVECTOR2(1.f, 1.f)));

	//위
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[4], D3DXVECTOR2(0.f, 0.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[7], D3DXVECTOR2(1.f, 0.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[5], D3DXVECTOR2(0.f, 1.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[6], D3DXVECTOR2(1.f, 1.f)));

	//오
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[6], D3DXVECTOR2(0.f, 0.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[7], D3DXVECTOR2(1.f, 0.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[2], D3DXVECTOR2(0.f, 1.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[3], D3DXVECTOR2(1.f, 1.f)));

	//뒤
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[7], D3DXVECTOR2(0.f, 0.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[4], D3DXVECTOR2(1.f, 0.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[3], D3DXVECTOR2(0.f, 1.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[0], D3DXVECTOR2(1.f, 1.f)));

	//앞
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[5], D3DXVECTOR2(0.f, 0.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[6], D3DXVECTOR2(1.f, 0.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[1], D3DXVECTOR2(0.f, 1.f)));
	m_vecVertex.push_back(ST_PT_VERTEX(vertex[2], D3DXVECTOR2(1.f, 1.f)));

	ST_PT_VERTEX* vertices;
	m_pVertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		vertices[i] = m_vecVertex[i];
	}

	m_pVertexBuffer->Unlock();

	D3DXCreateTextureFromFile(
		g_pD3DDevice,
		"./CH/SkyBox/Bottom.bmp",
		&m_pTexture[0]);

	D3DXCreateTextureFromFile(
		g_pD3DDevice,
		"./CH/SkyBox/Right.bmp",
		&m_pTexture[1]);

	D3DXCreateTextureFromFile(
		g_pD3DDevice,
		"./CH/SkyBox/Top.bmp",
		&m_pTexture[2]);

	D3DXCreateTextureFromFile(
		g_pD3DDevice,
		"./CH/SkyBox/Left.bmp",
		&m_pTexture[3]);

	D3DXCreateTextureFromFile(
		g_pD3DDevice,
		"./CH/SkyBox/Back.bmp",
		&m_pTexture[4]);

	D3DXCreateTextureFromFile(
		g_pD3DDevice,
		"./CH/SkyBox/Front.bmp",
		&m_pTexture[5]);
}

void cSkyBox::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &this->GetWorld( ));
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(ST_PT_VERTEX));
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);

	for (size_t i = 0; i < _countof(m_pTexture); i++)
	{ 
		g_pD3DDevice->SetTexture(0, m_pTexture[i]);
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}
	
}

void cSkyBox::Update()
{

}