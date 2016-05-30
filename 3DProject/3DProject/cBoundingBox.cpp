#include "stdafx.h"
#include "cBoundingBox.h"
#include "GameObject.h"

cBoundingBox::cBoundingBox( 
	GameObject* owner,
	const D3DXVECTOR3& vMin,
	const D3DXVECTOR3& vMax ) : 
	
	m_pBox(NULL),
	m_bWireDraw(false),
	m_vMin( vMin ),
	m_vMax( vMax ),
	ICollider( owner )
{
	D3DXVECTOR3 size = m_vMax - m_vMin;
	D3DXCreateBox(g_pD3DDevice, size.x, size.y, size.z, &m_pBox, nullptr);
}

cBoundingBox::~cBoundingBox()
{
	SAFE_RELEASE( m_pBox);
}

void cBoundingBox::Update( )
{
}

void cBoundingBox::Render()
{
	this->PreRender( );

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &this->GetOwner( )->GetWorld( ));
	g_pD3DDevice->SetTexture( 0, nullptr );
	m_pBox->DrawSubset( 0 );

	this->PostRender( );
}