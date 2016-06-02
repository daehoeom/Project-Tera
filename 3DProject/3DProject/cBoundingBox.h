#pragma once
#include "ICollider.h"


class cBoundingBox 
	: public ICollider
{
public:
	cBoundingBox( const D3DXVECTOR3& vMin, 
				  const D3DXVECTOR3& vMax );
	virtual ~cBoundingBox();

	virtual void Update() override;
	virtual void Render() override;

public:
	virtual eColliderType GetColliderType( ) const;

	D3DXVECTOR3 GetMinimum() const 
	{
		return m_vMin; 
	}
	D3DXVECTOR3 GetMaximum() const 
	{ 
		return m_vMax;
	}

	D3DXMATRIXA16 GetLocal() { return m_matLocalTM; }
	void SetLocal(D3DXMATRIXA16* local) { m_matLocalTM = *local; }

	D3DXMATRIXA16 GetWorld() { return m_matWorldTM; }
	void SetWorld(D3DXMATRIXA16* world) { m_matWorldTM = *world; }

private:
	ID3DXMesh*		m_pBox;
	bool			m_bWireDraw;
	D3DXVECTOR3		m_vMin;
	D3DXVECTOR3		m_vMax;
	D3DXMATRIXA16   m_matLocalTM;
	D3DXMATRIXA16	m_matWorldTM;

};

inline eColliderType cBoundingBox::GetColliderType( ) const
{
	return eColliderType::kBox;
}