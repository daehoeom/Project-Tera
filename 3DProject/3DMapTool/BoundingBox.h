#pragma once
#include "ICollider.h"


class BoundingBox :
	public ICollider
{
public:
	BoundingBox( 
		const D3DXVECTOR3& min, 
		const D3DXVECTOR3& max ) :
		m_min( min ),
		m_max( max ) {}
	virtual ~BoundingBox( ) {}

#ifdef _DEBUG
	virtual void Render( ) override;
#endif

	const D3DXVECTOR3& GetMin( ) const { return m_min; }
	const D3DXVECTOR3& GetMax( ) const { return m_max; }

private:
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
};
