#include "stdafx.h"
#include "cBoundingSphere.h"
#include "cGameObject.h"

cBoundingSphere::cBoundingSphere( D3DXVECTOR3 Pos, float radius ) :
	 sphereMesh( nullptr ) 
	,m_fRadius( radius )
	,m_vPosition(0, 0, 0)
{
	D3DXCreateSphere( g_pD3DDevice, radius, 16, 16, &sphereMesh, NULL );
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}

cBoundingSphere::~cBoundingSphere()
{
	SAFE_RELEASE(sphereMesh);
}

void cBoundingSphere::Update()
{
	m_matWorldTM = m_matLocalTM * m_matWorldTM;
	m_vPosition = D3DXVECTOR3(m_matWorldTM._41, m_matWorldTM._42, m_matWorldTM._43);
}

void cBoundingSphere::Render()
{
	this->PreRender( );
	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pD3DDevice->SetTexture(0, nullptr);
	sphereMesh->DrawSubset(0);

	this->PostRender( );
}