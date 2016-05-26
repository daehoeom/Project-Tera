#include "stdafx.h"
#include "cBoundingBox.h"


cBoundingBox::cBoundingBox( const char* name )
	: m_pBox(NULL)
	 ,m_bWireDraw(false)
	 ,m_vMin(0, 0,0)
	 ,m_vMax(0, 0, 0)
	 ,GameObject( name )
{
	D3DXMatrixIdentity(&m_matWorld);
	ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));
}

cBoundingBox::cBoundingBox( const char * name ) :
	GameObject( name )
{
}

cBoundingBox::~cBoundingBox()
{
	SAFE_RELEASE(m_pBox);
}

void cBoundingBox::Setup(D3DXVECTOR3* vMin, D3DXVECTOR3* vMax)
{
	m_vMin = *vMin;
	m_vMax = *vMax;
	D3DXVECTOR3 size = m_vMax - m_vMin;
	D3DXCreateBox(g_pD3DDevice, size.x, size.y, size.z, &m_pBox, nullptr);

	stMtl.Ambient = stMtl.Diffuse = stMtl.Specular = D3DXCOLOR(1.f, 1.f, 0.f, 1.f);
}

void cBoundingBox::Update(D3DXMATRIXA16* matWorld)
{
	m_matWorld = *matWorld;
}

void cBoundingBox::Render()
{
	if (m_bWireDraw)
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pD3DDevice->SetMaterial(&stMtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, nullptr);
	m_pBox->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}