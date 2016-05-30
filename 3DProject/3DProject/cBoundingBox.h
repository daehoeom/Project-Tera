#pragma once
#include "ICollider.h"
#include "shared_comptr.h"


class cBoundingBox 
	: public ICollider
{
public:
	cBoundingBox( class GameObject* owner, 
				  const D3DXVECTOR3& vMin, 
				  const D3DXVECTOR3& vMax );
	virtual ~cBoundingBox();

	virtual void Update() override;
	virtual void Render() override;

public:
	const D3DXVECTOR3& GetMinimum() { return m_vMin; }
	const D3DXVECTOR3& GetMaximum() { return m_vMax; }

private:
	shared_comptr<ID3DXMesh>	m_pBox;
	bool						m_bWireDraw;
	D3DXVECTOR3					m_vMin;
	D3DXVECTOR3					m_vMax;

};