#pragma once
#include "ICollider.h"


class cBoundingBox 
	: public ICollider
{
public:
	cBoundingBox( const D3DXVECTOR3& vMin, 
		const D3DXVECTOR3& vChange);
	virtual ~cBoundingBox();

	virtual void Update() override;
	virtual void Render() override;

public:
	virtual eColliderType GetColliderType( ) const;

	void SetPosition(const D3DXVECTOR3& pos) override { m_vMin = pos; }

	D3DXVECTOR3& GetPosition() override { return m_vMax - m_vMin; }
	const D3DXVECTOR3& GetPosition() const override	{ return m_vMax - m_vMin; }

	D3DXVECTOR3 GetMinimum() const  
	{ 
		return m_vMin; 
	}
	void SetMinumum(D3DXVECTOR3& vMin) { m_vMin = vMin; }

	D3DXVECTOR3 GetMaximum() const { return m_vMax; }
	void SetMaximum(D3DXVECTOR3& vMax) { m_vMax = vMax; }

	D3DXMATRIXA16 GetLocal() override{ return m_matLocalTM; }
	void SetLocal(D3DXMATRIXA16* local) override { m_matLocalTM = *local; }

	D3DXMATRIXA16 GetWorld() override { return m_matWorldTM; }
	void SetWorld(D3DXMATRIXA16* world) override { m_matWorldTM = *world; }

private:
	ID3DXMesh*		m_pBox;
	bool			m_bWireDraw;
	D3DXVECTOR3		m_vMin;
	D3DXVECTOR3		m_vMax;
	D3DXVECTOR3		m_vChange;
	D3DXMATRIXA16   m_matLocalTM;
	D3DXMATRIXA16	m_matWorldTM;

};

inline eColliderType cBoundingBox::GetColliderType( ) const
{
	return eColliderType::kBox;
}