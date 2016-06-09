#pragma once
#include "ICollider.h"


class BoundingBox :
	public ICollider
{
public:
	BoundingBox(
		const D3DXVECTOR3& min,
		const D3DXVECTOR3& max );
	virtual ~BoundingBox( );

	virtual void Update( ) override;
	virtual void Render( const D3DXMATRIXA16& TM ) override;

	void SetMinMax( 
		const D3DXVECTOR3& min, 
		const D3DXVECTOR3& max );
	const D3DXVECTOR3& GetMin( ) const { return m_min; }
	const D3DXVECTOR3& GetMax( ) const { return m_max; }

private:
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
	std::vector<ST_PC_VERTEX> m_vertices;
	std::vector<DWORD> m_indices;
	const DWORD m_color = 0xffffff;
	const float m_interval = 0.1f;
};
