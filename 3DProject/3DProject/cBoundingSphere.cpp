#include "stdafx.h"
#include "cBoundingSphere.h"


cBoundingSphere::cBoundingSphere()
	: sphereMesh(NULL)
	, m_bWireDraw(false)
	, GameObject(cBoundingSphere())
{
	D3DXMatrixIdentity(&m_matWorld);
	ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));
}

cBoundingSphere::~cBoundingSphere()
{
	SAFE_RELEASE(sphereMesh);
}

void cBoundingSphere::Setup(D3DXVECTOR3* vCenter, float radius)
{
	//바운딩 구의 중심점을 설정한다.
	SetPosition(*vCenter);
	
	D3DXCreateSphere(g_pD3DDevice, radius, 16, 16, &sphereMesh, NULL);

	stMtl.Ambient = stMtl.Diffuse = stMtl.Specular = D3DXCOLOR(1.f, 1.f, 0.f, 1.f);
}

void cBoundingSphere::Update(D3DXMATRIXA16* matWorld)
{
	m_matWorld = *matWorld;
}

void cBoundingSphere::Render()
{
	if (m_bWireDraw)
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pD3DDevice->SetMaterial(&stMtl);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetTexture(0, nullptr);
	sphereMesh->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}