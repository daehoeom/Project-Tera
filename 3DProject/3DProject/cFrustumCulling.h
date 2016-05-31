#pragma once

#include "cBoundingSphere.h"

class cFrustumCulling
{
public:
	cFrustumCulling();
	~cFrustumCulling();

	void Setup();
	void Update();

	bool IsInFrustum(cBoundingSphere* bs);

private:
	std::vector<D3DXVECTOR3>  projectionSpacePointArray;
	std::vector<D3DXPLANE>   frustumPlaneArray;
};

