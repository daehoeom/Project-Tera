#include "stdafx.h"
#include "cBoundingSphere.h"


cBoundingSphere::cBoundingSphere()
	: sphereMesh(NULL)
	, m_bWireDraw(false)
	, GameObject(cBoundingSphere())
{
	D3DXMatrixIdentity(&m_matWorld);
}


cBoundingSphere::~cBoundingSphere()
{
	SAFE_RELEASE(sphereMesh);
}

void cBoundingSphere::Setup(D3DXVECTOR3* vCenter, float radius)
{

}

void cBoundingSphere::Update()
{

}

void cBoundingSphere::Render()
{

}