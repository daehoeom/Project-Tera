#include "stdafx.h"
#include "cBoundingSphere.h"

#include "cGameObject.h"

cBoundingSphere::cBoundingSphere( cGameObject* owner )
	: sphereMesh(NULL)
	, ICollider( owner )
{
}

cBoundingSphere::~cBoundingSphere()
{
	SAFE_RELEASE(sphereMesh);
}

void cBoundingSphere::Setup(D3DXVECTOR3* vCenter, float radius)
{
	//바운딩 구의 중심점을 설정한다.
	this->GetOwner( )->SetPosition(*vCenter);
	
	D3DXCreateSphere(g_pD3DDevice, radius, 16, 16, &sphereMesh, NULL);
}

void cBoundingSphere::Update()
{
}

void cBoundingSphere::Render()
{
	this->PreRender( );

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &this->GetOwner( )->GetWorld( ));
	sphereMesh->DrawSubset( 0 );

	this->PostRender( );
}