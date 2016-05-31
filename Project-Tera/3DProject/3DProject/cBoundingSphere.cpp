#include "stdafx.h"
#include "cBoundingSphere.h"

#include "cGameObject.h"

cBoundingSphere::cBoundingSphere( 
	cGameObject* owner, 
	float radius ) :
	
	sphereMesh( nullptr ), 
	m_fRadius( radius ),
	ICollider( owner )
{
	D3DXCreateSphere( g_pD3DDevice, radius, 16, 16, &sphereMesh, NULL );
}

cBoundingSphere::~cBoundingSphere()
{
}

void cBoundingSphere::Update()
{
}

void cBoundingSphere::Render()
{
	this->PreRender( );

	if ( this->GetOwner( ))
	{
		g_pD3DDevice->SetTransform( D3DTS_WORLD, &this->GetOwner( )->GetWorld( ) );
		g_pD3DDevice->SetTexture( 0, nullptr );
		sphereMesh->DrawSubset( 0 );
	}

	this->PostRender( );
}