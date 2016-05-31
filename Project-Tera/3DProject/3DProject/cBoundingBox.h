#pragma once
#include "ICollider.h"
#include "shared_comptr.h"


class cBoundingBox 
	: public ICollider
{
public:
	cBoundingBox( class cGameObject* owner, 
				  const D3DXVECTOR3& vMin, 
				  const D3DXVECTOR3& vMax );
	virtual ~cBoundingBox();

	virtual void Update() override;
	virtual void Render() override;

public:
	virtual eColliderType GetColliderType( ) const;

	D3DXVECTOR3 GetMinimum() const 
	{
		return m_vMin + GetOwner( )->GetPosition(); 
	}
	D3DXVECTOR3 GetMaximum() const 
	{ 
		return m_vMax + GetOwner( )->GetPosition( );
	}

private:
	shared_comptr<ID3DXMesh>	m_pBox;
	bool						m_bWireDraw;
	D3DXVECTOR3					m_vMin;
	D3DXVECTOR3					m_vMax;

};

inline eColliderType cBoundingBox::GetColliderType( ) const
{
	return eColliderType::kBox;
}