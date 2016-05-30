#include "stdafx.h"
#include "cBoundingBox.h"
#include "GameObject.h"

cBoundingBox::cBoundingBox( GameObject* owner )
	: m_pBox(NULL)
	 ,m_bWireDraw(false)
	 ,m_vMin(0, 0,0)
	 ,m_vMax(0, 0, 0)
	 ,ICollider( owner )
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