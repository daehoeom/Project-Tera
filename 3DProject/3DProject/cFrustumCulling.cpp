#include "stdafx.h"
#include "cFrustumCulling.h"
#include "cBoundingSphere.h"

cFrustumCulling::cFrustumCulling()
{
}


cFrustumCulling::~cFrustumCulling()
{
}

void cFrustumCulling::Setup()
{
	projectionSpacePointArray.clear();
	projectionSpacePointArray.resize(8);
	projectionSpacePointArray[0] = D3DXVECTOR3(-1, -1, 0);
	projectionSpacePointArray[1] = D3DXVECTOR3(-1, -1, 1);
	projectionSpacePointArray[2] = D3DXVECTOR3(1, -1, 1);
	projectionSpacePointArray[3] = D3DXVECTOR3(1, -1, 0);
	projectionSpacePointArray[4] = D3DXVECTOR3(-1, 1, 0);
	projectionSpacePointArray[5] = D3DXVECTOR3(-1, 1, 1);
	projectionSpacePointArray[6] = D3DXVECTOR3(1, 1, 1);
	projectionSpacePointArray[7] = D3DXVECTOR3(1, 1, 0);

	frustumPlaneArray.clear();
	frustumPlaneArray.resize(6);
}

void cFrustumCulling::Update()
{
	D3DXMATRIXA16 projection, view;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &projection);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &view);

	std::vector<D3DXVECTOR3> frustum(8);
	for (size_t i = 0; i < projectionSpacePointArray.size(); ++i)
	{
		D3DXVec3Unproject(
			&frustum[i],
			&projectionSpacePointArray[i],
			nullptr,
			&projection,
			&view,
			nullptr
			);
	}

	D3DXPlaneFromPoints(&frustumPlaneArray[0],
		&frustum[0], &frustum[3], &frustum[2]);	//아래
	D3DXPlaneFromPoints(&frustumPlaneArray[1],
		&frustum[7], &frustum[6], &frustum[2]);	//오른쪽
	D3DXPlaneFromPoints(&frustumPlaneArray[2],
		&frustum[6], &frustum[5], &frustum[1]);	//far
	D3DXPlaneFromPoints(&frustumPlaneArray[3],
		&frustum[5], &frustum[4], &frustum[0]);	//왼쪽
	D3DXPlaneFromPoints(&frustumPlaneArray[4],
		&frustum[4], &frustum[7], &frustum[3]);	//near
	D3DXPlaneFromPoints(&frustumPlaneArray[5],
		&frustum[5], &frustum[6], &frustum[7]);	//위
}

bool cFrustumCulling::IsInFrustum(cBoundingSphere* bs)
{
	for (size_t i = 0; i < frustumPlaneArray.size(); ++i)
	{
		if ( D3DXPlaneDotCoord(&frustumPlaneArray[i], 
				&bs->GetOwner( )->GetPosition()) > bs->GetRadius())
		{
			return false;
		}
	}

	return true;
}