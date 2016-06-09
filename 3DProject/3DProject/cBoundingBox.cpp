#include "stdafx.h"
#include "cBoundingBox.h"
#include "cGameObject.h"


cBoundingBox::cBoundingBox(
	const D3DXVECTOR3& vMin,
	const D3DXVECTOR3& vChange ) : 
	m_pBox(NULL),
	m_bWireDraw(false),
	m_vMin( vMin ),
	m_vChange(vChange)
{
	m_vMax = m_vMin + m_vChange;
	D3DXVECTOR3 size = m_vMax - m_vMin;
	D3DXCreateBox(g_pD3DDevice, size.x, size.y, size.z, &m_pBox, nullptr);
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}

cBoundingBox::~cBoundingBox()
{
	SAFE_RELEASE(m_pBox);
}

void cBoundingBox::Update( )
{
	m_matWorldTM = m_matLocalTM * m_matWorldTM;

	m_vMin = D3DXVECTOR3(m_matWorldTM._41, m_matWorldTM._42, m_matWorldTM._43);
	m_vMax = m_vMin + m_vChange;
}

void cBoundingBox::Render()
{
	this->PreRender( );

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pD3DDevice->SetTexture( 0, nullptr );
	m_pBox->DrawSubset( 0 );

	this->PostRender( );
}


