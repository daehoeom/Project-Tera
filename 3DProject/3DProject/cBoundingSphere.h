#pragma once
#include "ICollider.h"

class cBoundingSphere : 
	public ICollider
{
public:
	cBoundingSphere( class GameObject* owner );
	virtual ~cBoundingSphere();

	void Setup(D3DXVECTOR3* vCenter, float radius);
	virtual void Update() override;
	virtual void Render() override;

	float GetRadius( ) const { return m_fRadius; }
	void SetRadius( float radius ) { m_fRadius = radius; }

private:
	LPD3DXMESH	sphereMesh;
	float		m_fRadius;
};

