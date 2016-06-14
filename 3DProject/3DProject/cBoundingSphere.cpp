#include "stdafx.h"
#include "cBoundingSphere.h"
#include "cGameObject.h"
#include "Console.h"

cBoundingSphere::cBoundingSphere( D3DXVECTOR3 Pos, float radius ) :
	 sphereMesh( nullptr ) 
	,m_fRadius( radius )
	,m_vPosition(0, 0, 0)
{
	D3DXCreateSphere( g_pD3DDevice, radius, 16, 16, &sphereMesh, NULL );
	D3DXMatrixIdentity(&m_matLocal);
	D3DXMatrixIdentity(&m_matWorld);
}

cBoundingSphere::~cBoundingSphere()
{
	SAFE_RELEASE(sphereMesh);
}

void cBoundingSphere::Update()
{
	m_matWorld *= m_matLocal;
	m_vPosition = D3DXVECTOR3(m_matWorld._41, m_matWorld._42, m_matWorld._43);
}

void cBoundingSphere::Render()
{
	this->PreRender( );
	
	//월드매트릭스 갱신 안되서;; 넣음
	m_matWorld = m_matWorld * m_matLocal;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, nullptr);
	sphereMesh->DrawSubset(0);

	this->PostRender( );
}