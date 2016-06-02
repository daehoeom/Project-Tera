#include "stdafx.h"
#include "cBoundingBox.h"
#include "cGameObject.h"


cBoundingBox::cBoundingBox(
	const D3DXVECTOR3& vMin,
	const D3DXVECTOR3& vMax ) : 
	
	m_pBox(NULL),
	m_bWireDraw(false),
	m_vMin( vMin ),
	m_vMax( vMax )
{
	D3DXVECTOR3 size = m_vMax - m_vMin;
	D3DXCreateBox(g_pD3DDevice, size.x, size.y, size.z, &m_pBox, nullptr);
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}

cBoundingBox::~cBoundingBox()
{
}

void cBoundingBox::Update( )
{
	m_matWorldTM = m_matLocalTM * m_matWorldTM;
}

void cBoundingBox::Render()
{
	this->PreRender( );

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pD3DDevice->SetTexture( 0, nullptr );
	m_pBox->DrawSubset( 0 );

	this->PostRender( );
}


