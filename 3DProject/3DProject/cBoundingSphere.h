#pragma once
#include "ICollider.h"
#include "shared_comptr.h"

class cGameObject;
class cBoundingSphere : 
	public ICollider
{
public:
	cBoundingSphere( cGameObject* owner, float radius );
	virtual ~cBoundingSphere();

	virtual void Update() override;
	virtual void Render() override;

	virtual eColliderType GetColliderType( ) const override;
	
public:
	float GetRadius( ) const { return m_fRadius; }
	void SetRadius( float radius ) { m_fRadius = radius; }

private:
	shared_comptr<ID3DXMesh> sphereMesh;
	float m_fRadius;
};

inline eColliderType cBoundingSphere::GetColliderType( ) const
{
	return eColliderType::kSphere;
}