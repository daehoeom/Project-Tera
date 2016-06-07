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

	void SetPosition(const D3DXVECTOR3& vPos) { m_vPosition = vPos; }
	D3DXVECTOR3& GetPosition() override { return m_vPosition; };
	const D3DXVECTOR3& GetPosition() const override { return m_vPosition; };

private:
	ID3DXMesh*		sphereMesh;
	float			m_fRadius;
	D3DXVECTOR3		m_vPosition;
};

inline eColliderType cBoundingSphere::GetColliderType( ) const
{
	return eColliderType::kSphere;
}