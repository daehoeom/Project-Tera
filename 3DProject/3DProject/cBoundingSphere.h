#pragma once
#include "ICollider.h"

class cBoundingSphere : 
	public ICollider
{
public:
	cBoundingSphere( D3DXVECTOR3 Position, float radius );
	virtual ~cBoundingSphere();

	virtual void Update() override;
	virtual void Render() override;

	virtual eColliderType GetColliderType( ) const override;
	
public:
	float GetRadius( ) const { return m_fRadius; }
	void SetRadius( float radius ) { m_fRadius = radius; }

	D3DXVECTOR3 GetPosition() const { return m_vPosition; }
	void SetPosition(D3DXVECTOR3 vPos) { m_vPosition = vPos; }

private:
	ID3DXMesh*		sphereMesh;
	float			m_fRadius;
	D3DXVECTOR3		m_vPosition;
};

inline eColliderType cBoundingSphere::GetColliderType( ) const
{
	return eColliderType::kSphere;
}